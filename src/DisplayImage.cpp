#ifndef DISPLAY_IMAGE
#define DISPLAY_IMAGe

int display(string path) {
    Mat image;
    image = imread( path, 1 );

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
}


#endif