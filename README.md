# Tech Challenge
## Project Structure

I have *main.cpp* as the main entrypoint for the application. The code for the application library is found in the src fodler and exposes three classes. *ImageAlign* has a single public function that takes the path of a transformed image and a reference image and aligns the first onto the second. The rest of the methods in this class are helpers. The *ImageAlign* is dependant on the *ImageReader* interface. In the application, I use the *ROIReader* implementation to allow users to crop the image before the alignment. In the tests, I use a *TestReader* that simply opens the image without modifying it. All images are opened in grayscale.

The libs folder contains the GoogleTest dependency.

## Instructions
### Running the application on a Linux environment with OpenCV installed

```bash
git submodule update --init --recursive
mkdir build && cd build
cmake ..
cmake --build .
cd .. && build/Manipulations
```

### Running the tests in a Linux environment with OpenCV installed

```bash
git submodule update --init --recursive
mkdir build && cd build
cmake ..
cmake --build .
cd .. && build/test/Tests
```

### Running the tests in a Docker Container

```bash
docker build . --tag manipulations
docker run manipulations:latest
```

## Improvements

### Code improvements

   1. Because I store paths in strings, my code could onyl be compiled on a linux platform. I could improve the code by storing paths in a better data structure (e.g. using the boost library). The functionality of this data structure would most likely cover the *getParentDirectory* and *addAlignSuffix* that are incorrectly placed in the ImageAlign class.
   2. Filesystem access should be done through a proxy. As of now, my unit tests are not completely independant (they rely on access to local files). The ImageReader class serves as a proxy for accessing local files, but having another proxy for writing would allow me to write stubs that would completely isolate my unit tests. Integration tests could later be written that would take into account a filesystem.
   3. The unit test that I wrote is very very basic. Given that I don't have branching paths in my code, that single Unit test gives my a 100% coverage. Nonetheless, developping techniques to verify the alignment quality could be very benificial. I'm missing theoretical knowledge to be able to write this kind of test.
   4. Cropping the images could leave no overlap between the transformed image and the reference image. I would want to implement a piece of code that can detect when the contents of the two images are mutually exclusive.
   5. I've noticed some photometric distortion between the two images. I would try to use the ECC algorithm to align the pictures to see if the results are improved.

### DevOps imrprovements
1. I don't address the cross-compilation of my code for an ARM platform. I didn't have time to setup an emulator and I didn't have a machine on hand to validate my code. As such I decided not to do it. Had I gotten easy access to an ARM platform, the following steps would've necessary to validate my code.
   1. OpenCV has a tutorial that explains how to use CMake to change the target platform. The address the ARM platform.
   2. I could then use the same mechanism to cross-compile my unit tests.
   3. Using SCP I could move the files from my computer to the ARM platform and then SSH into that machine to execute the tests.
2. The Docker container could be made a lot lighter. The installation of Ubuntu, all of the OpenCV dependencies and OpenCV inside of the container takes a long time. Although this installation only has to be done a single time, the resulting container is quite heavy and is full of useless functionality. Using Alpine Linux or a FROM Scratch container with minimal dependencies would be a good way to lighten that container.
   1. I would also find a way to compile the googletest library before copying the project files to the docker image.

## References
https://linuxize.com/post/how-to-install-opencv-on-ubuntu-20-04/
https://rtfm.co.ua/en/docker-configure-tzdata-and-timezone-during-build/
https://www.learnopencv.com/image-alignment-ecc-in-opencv-c-python/
https://www.learnopencv.com/image-alignment-ecc-in-opencv-c-python/