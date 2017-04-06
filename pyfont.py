#!/usr/bin/env python

from PIL import Image
from operator import or_
from string import Template
from itertools import islice
import logging
import argparse

fileTemplate = Template(
"""
#ifndef ${fontName}_H
#define ${fontName}_H

#include "pyfont.h"

namespace ${fontName}
{
    const uint8_t data[] =
    {
$rawData
    };
    const uint16_t offsets[] =
    {
$offsets
    };
    const uint8_t sizes[] =
    {
$sizes
    };

    const PyFont font($chars, $baseChar, data, offsets, sizes);
}

#endif //${fontName}_H
"""
)

def twoDigitHex(i):
    return "0x{:02X}".format(i)

def threeDigitHex(i):
    return "0x{:03X}".format(i)

def chunks(l, n):
    """Yield successive n-sized chunks from l."""
    for i in range(0, len(l), n):
        yield l[i:i + n]

def formatHexData(data, elementsPerRow = 16, conv=twoDigitHex):
    rows = []
    for row in chunks(data, 16):
        rows.append("\t\t\t"+ ", ".join(map(conv, row)))

    return ",\n".join(rows)


def makeFont(pngFilename, fontName, baseChar, eraseSpace = None):
    logging.info("Opening file %s", pngFilename)
    with Image.open(pngFilename) as image:
        height = image.size[1]
        width = image.size[0]
        logging.info("Loaded image: {}x{}".format(height, width))
        assert(height == 8)
        rows = range(height)

        rawData = []
        charSizes = []
        charOffsets = []

        currentCharData = []

        for x in range(width):
            column = reduce(or_, map(lambda y: (image.getpixel((x,y)) == 0) * 2**y , rows))
            if column != 0:
                currentCharData.append(column)
                continue

            if len(currentCharData) == 0:       #discard empty chars
                logging.debug("Skipping empty character...");
                continue
            charSizes.append(len(currentCharData))        #size of current char
            charOffsets.append(len(rawData))              #offset in the raw table
            rawData.extend(currentCharData)               #append to raw data and clear

            logging.debug("{} - size: {} offset: {}".format(len(charSizes), charSizes[-1], charOffsets[-1]))
            currentCharData = []

        if not eraseSpace is None:
            logging.info("Erasing empty character at offset %d", eraseSpace)
            start = charOffsets[eraseSpace]
            stop = start+charSizes[eraseSpace]
            for i in range(start, stop):
                rawData[i] = 0;

        totalSize = len(charSizes) + len(charOffsets)*2 + len(rawData)

        logging.info("Detected %d characters",len(charSizes))
        logging.info("Raw data lenght: %d", len(rawData))
        logging.info("Total data size: %d", totalSize)

        fileContents = fileTemplate.substitute(fontName = fontName,
                                rawData = formatHexData(rawData, 16),
                                sizes = formatHexData(charSizes, 16),
                                offsets = formatHexData(charOffsets, 16, conv=threeDigitHex),
                                chars = len(charSizes),
                                baseChar = baseChar)

        logging.info("Writing font data into a file: %s", fontName + ".h")
        with open(fontName+".h", "w+") as f:
            f.write(fileContents)

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO, format="%(asctime)s %(message)s")
    parser = argparse.ArgumentParser(description="A tool to convert fonts in PNG files into fonts");
    parser.add_argument("pngFile", type=file)
    parser.add_argument("fontName")
    parser.add_argument("--firstChar", type=int, default=32)
    parser.add_argument("--clearSpace", type=int, default=0)

    args = parser.parse_args()

    makeFont(args.pngFile, args.fontName, args.firstChar, args.clearSpace)
