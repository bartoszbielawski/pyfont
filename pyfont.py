

from PIL import Image
from operator import or_
from string import Template

fileTemplate = Template(
"""
#ifndef ${fontName}_H
#define ${fontName}_H

#include "pyfont.h"

namespace ${fontName}
{
    const uint8_t data[] = {$rawData};
    const uint16_t offsets[] = {$offsets};
    const uint8_t sizes[] = {$sizes};

    const PyFont font($chars, $baseChar, data, offsets, sizes);
}

#endif //${fontName}_H
"""
)

def makeFont(pngFilename, fontName, baseChar, eraseSpace = None):

    with Image.open(pngFilename) as image:
        height = image.size[1]
        width = image.size[0]
        print("Loaded image: {}x{}".format(height, width))

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
                continue

            charSizes.append(len(currentCharData))        #size of current char
            charOffsets.append(len(rawData))              #offset in the raw table
            rawData.extend(currentCharData)               #append to raw data and clear

            print("{} - size: {} offset: {}".format(len(charSizes), charSizes[-1], charOffsets[-1]))
            currentCharData = []

        if not eraseSpace is None:
            start = charOffsets[eraseSpace]
            stop = start+charSizes[eraseSpace]
            for i in range(start, stop):
                rawData[i] = 0;

        fileContents = fileTemplate.substitute(fontName = fontName,
                                rawData = ", ".join(map(hex, rawData)),
                                sizes = ", ".join(map(hex, charSizes)),
                                offsets = ", ".join(map(hex, charOffsets)),
                                chars = len(charSizes),
                                baseChar = baseChar)

        print(fileContents)

        with open(fontName+".h", "w+") as f:
            f.write(fileContents)

if __name__ == "__main__":
    makeFont("font.png", "myTestFont", 32, 0)
