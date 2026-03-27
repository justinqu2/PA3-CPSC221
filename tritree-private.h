/**
 * @file tritree-private.h
 * @author (Your CWLs here)
 * @description TriTree private function declarations, CPSC 221 PA3
 *
 * This file must be submitted for grading,
 * even if you do not add anything to it.
 *
 * Declare your functions here as if they are written in-line
 * starting from line 220 of tritree.h
**/

// Gets the average colour in the given borders (ul in (x, y))
// UNUSED
RGBAPixel getAvgColour(pair<int, int> ul, int w, int h, PNG &im) { 
    unsigned long avgR = 0;
    unsigned long avgG = 0;
    unsigned long avgB = 0;
    int size = w*h;

    for (int r = ul.second; r < h + ul.second; r++) {
        for (int c = ul.first; c < w + ul.first; c++) {
            avgR += im.getPixel(c, r)->r;
            avgG += im.getPixel(c, r)->g;
            avgB += im.getPixel(c, r)->b;
        }
    }

    avgR /= size;
    avgG /= size;
    avgB /= size;

    RGBAPixel avgPix((int) avgR, (int) avgG, (int)avgB);
    return avgPix;
}

// Calculates weighted avg from children (preferable to above)
RGBAPixel weightedAvg(Node* parent) const {
    long areaA = (long)(parent->A->width * parent->A->height);
    long areaB = 0;
    long areaC = (long)(parent->C->width * parent->C->height);

    long sumR = (parent->A->avg.r * areaA) + (parent->C->avg.r * areaC);
    long sumG = (parent->A->avg.g * areaA) + (parent->C->avg.g * areaC);
    long sumB = (parent->A->avg.b * areaA) + (parent->C->avg.b * areaC);

    // Middle child may be null
    if (parent->B != nullptr) {
        areaB = (long)(parent->B->width * parent->B->height);
        sumR += (parent->B->avg.r * areaB);
        sumG += (parent->B->avg.g * areaB);
        sumB += (parent->B->avg.b * areaB);
    }

    long totalArea = areaA + areaB + areaC;

    return RGBAPixel((int) sumR/totalArea, (int) sumG/totalArea, (int) sumB/totalArea);
}

// Returns { {ulx, uly, w, h} } for A, B, and C in order
void splitThree(pair<int, int> ul, int w, int h, 
                         pair<int, int>& ulA, int& wA, int& hA, 
                         pair<int, int>& ulB, int& wB, int& hB, 
                         pair<int, int>& ulC, int& wC, int& hC) {

    if (w >= h) { // Split width (new cols) on equal dimensions
        int base = w / 3;
        int rem = w % 3;
        
        if (rem == 0) { // Square
            wA = base; 
            wB = base; 
            wC = base;
        }
        else if (rem == 1) { // Middle gets extra width
            wA = base; 
            wB = base + 1; 
            wC = base; 
        }

        else { // Outer get extra width
            wA = base + 1; 
            wB = base;     
            wC = base + 1; 
        }

        hA = hB = hC = h; // Height unchanged
        ulA = ul;
        ulB = {ul.first + wA, ul.second};
        ulC = {ul.first + wA + wB, ul.second};
        
    } 
    
    else { 
        // Split height (new rows)
        int base = h / 3;
        int rem = h % 3;
        
        if (rem == 0) { 
            hA = base;     
            hB = base;     
            hC = base; 
        }
        else if (rem == 1) { 
            hA = base;     
            hB = base + 1; 
            hC = base; 
        }
        else { 
            hA = base + 1; 
            hB = base;     
            hC = base + 1; 
        }

        wA = wB = wC = w; // Width unchanged
        ulA = ul;
        ulB = {ul.first, ul.second + hA};
        ulC = {ul.first, ul.second + hA + hB};
    }
}

// Returns { {ulx, uly, w, h} } for A and C in order
void splitTwo(pair<int, int> ul, int w, int h, 
                       pair<int, int>& ulA, int& wA, int& hA, 
                       pair<int, int>& ulC, int& wC, int& hC) {
    // Split along two pixels
    if (w >= h) { 
        wA = 1; 
        wC = 1;
        hA = h;
        hC = h;

        ulA = ul;
        ulC = {ul.first + 1, ul.second}; // C is 1 pixel right of A
    } else {
        hA = 1; 
        hC = 1;
        wA = w;
        wC = w;

        ulA = ul;
        ulC = {ul.first, ul.second + 1}; // C is 1 pixel below A
    }
}

int countLeaves(Node* nd) const {
    // Base case: leaf node
    if (nd->A == nullptr) {
        return 1;
    }

    int count = 0;
    count += countLeaves(nd->A);
    count += countLeaves(nd->C);
    if (nd->B != nullptr) count += countLeaves(nd->B); // May not have B child

    return count;
}

// Plots leaf nodes onto input image
void renderImage(PNG &img, Node *nd) const {
    // Base case: leaf
    if (nd->A == nullptr) {
        int h = nd->height;
        int w = nd->width;
        int yCorner = nd->upperleft.second;
        int xCorner = nd->upperleft.first;

        // Write to image
        for (int y = yCorner; y < h + yCorner; y++) {
            for (int x = xCorner; x < w + xCorner; x++) {
                *(img.getPixel(x, y)) = nd->avg;
            }
        }

        return;
    }

    renderImage(img, nd->A);
    renderImage(img, nd->C);
    if (nd->B != nullptr) renderImage(img, nd->B);
}