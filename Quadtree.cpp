/*
Assume some binary (each pixel is either black or white ) images, have same 
width and height, and the length is power of 2. Present it by quadtree: 
divide the image into quarters, each quarter can be all back, all white or 
mixed, subdivide the mixed ones�� recurse.

+-------+---+---+
|         | F | F  |
|   T    +---+---+
|         | T | T  |
+---+--+---+---+
| F | T  |         |
+--+---+   F    |
| F | T  |         |
+--+- +------ --+

*/

//how to present this image

struct TreeNode {
    TreeNode* upperLeft;
    TreeNode* downLeft;
    TreeNode* upperRight;
    TreeNode* downRight;
    int size;
    bool pixel;
    TreeNode(bool p, int s): pixel(p), size(s), upperLeft(NULL), downLeft(
NULL), upperRight(NULL), downRight(NULL){}
};

TreeNode* copy( TreeNode* root) {
    if( !root) return NULL;
    TreeNode* r = new TreeNode( root->pixel, root->size);
    r->upperLeft = copy( root->upperLeft);
    r->upperRight = copy( root->upperRight);
    r->downLeft = copy( root->downLeft);
    r->downRight = copy( root->downRight);
    return r;
}
/* 
For each node, it is a leaf node or node always with 4 
children. Thus we can only check whether root!=NULL.
*/

// count all the black pixels of this image

int getBlackPixels( TreeNode* root) {
    if(!root) return 0;
    if( !root->upperLeft) { //only need check one
        if( root->pixel)
            return root->size * root->size;
    }
    int sum = 0;
    sum += getBlackPixels( root->upperLeft);
    sum += getBlackPixels( root->downLeft);
    sum += getBlackPixels( root->upperRight);
    sum += getBlackPixels( root->downRight);
    return sum;
}

// merge two images with  same size

TreeNode* mergeHelper( TreeNode* image1, TreeNode* image2) {
        
    if( !image1->pixel) {
        return new TreeNode(image1->pixel, image1->size);
    } 
    return copy(image2);
}

TreeNode* merge( const TreeNode* image1, const TreeNode* image2) {
    if( !image1->upperLeft && !image2->upperLeft) {
        return new TreeNode(image1->pixel && image2->pixel, image1->size);
}
    if( !image1->upperLeft) {
        return mergeHelper(image1, image2);
    }
    if( !image2->upperLeft) {
        return mergeHelper(image2, image1);
    }
    TreeNode* root = new TreeNode(image1->pixel && image2->pixel, image1->size);
    root->upperLeft = merge( image1->upperLeft, image2->upperLeft);
    root->upperRight = merge( image1->upperRight, image2->upperRight);
    root->downLeft = merge( image1->downLeft, image2->downLeft);
    root->downRight = merge( image1->downRight, image2->downRight);
    return root;
}

    




