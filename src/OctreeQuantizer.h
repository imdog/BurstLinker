//
// Created by succlz123 on 17-9-12.
//

#ifndef BURSTLINKER_OCTREEQUANTIZER_H
#define BURSTLINKER_OCTREEQUANTIZER_H

#include "ColorQuantizer.h"

namespace blk {

    class OctreeQuantizer : public ColorQuantizer {

    protected:

        typedef struct Node {
            bool isLeaf;
            uint8_t colorIndex;
            uint32_t pixelCount;
            uint32_t rSum;
            uint32_t gSum;
            uint32_t bSum;
            Node *child[8];
            Node *next;
        } Node;

    public:

        ~OctreeQuantizer() override;

        int32_t quantize(RGB *pixels, uint32_t pixelCount, uint32_t maxColorCount, RGB out[]) override;

        int32_t getColorIndex(uint8_t r, uint8_t g, uint8_t b) const;

        void getColorIndices(RGB pixels[], uint8_t *out, uint32_t size, int (*getOffset)(int, int));

        void freeTree(Node *&tree);

    protected:

        bool addColor(Node *&node, uint32_t r, uint32_t g, uint32_t b, int level);

        Node *createNode(int inLevel);

        void reduceTree();

        void getColorPalette(Node *tree, int32_t &inIndex, RGB out[]);

        size_t leafCount = 0;

        Node *octree{};

        Node *nodeList[8]{};
    };

}

#endif //BURSTLINKER_OCTREEQUANTIZER_H
