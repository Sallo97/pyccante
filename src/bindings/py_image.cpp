// This file contains the binding of the Piccante's Image class.


#include "py_image.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the Image class to the passed module.
 */
void init_Image(pybind11::module_ &m)
{
    // Defines the Image class in the passed module.
    py::class_<pic::Image>(m, "Image")

        // region Constructors


        /**
        * @brief the basic constructor of an Image
        */
        .def(py::init<>(),
            "Makes an empty image",
            py::return_value_policy::take_ownership)

        /**
         * @brief Image loads an Image from a file on the disk.
         * @param nameFile is the file name.
         * @param typeLoad is an option for LDR images only:
         * LT_NOR means that the input image values will be normalized in [0,1].
         * LT_NOR_GAMMA means that the input image values will be normalized in [0,1], and
         * gamma correction 2.2 will be removed.
         * LT_NONE means that image values are not modified during the loading.
         *
         * The default value is LT_NOR_GAMMA assuming that
         * we are storing normalized and linearized values in Image.
         */
        .def(py::init<std::string &, pic::LDR_type>(),
            py::return_value_policy::take_ownership,
            "Image loads an Image from a file on the disk.",
            py::arg("nameFile"), py::arg("typeLoad")=pic::LDR_type::LT_NOR_GAMMA)

        /**
         * @brief Image creates an Image with a given size.
         * @param width is the horizontal size in pixels.
         * @param height is the vertical size in pixels.
         * @param channels is the number of color channels.
         */
        .def(py::init<int, int, int>(),
             "Image creates an Image with a given width, height and numer of channels.",
            py::return_value_policy::take_ownership,
            py::arg("width"), py::arg("height"),
            py::arg("channels"))

        /**
         * @brief Image embeds an existing image in the new image.
         * @param imgIn is the input image to embed.
         * @param deepCopy enables a deep copy of img into this.
         */
        .def(py::init<pic::Image *, bool>(),
            "Image embeds an existing image in the new image.",
            py::return_value_policy::take_ownership,
            py::arg("imgIn"), py::arg("deepCopy"))

        /**
         * @brief Image embeds an array of float inside an Image.
         * @param color is the pointer to an array of float values.
         * @param channels is the color's number of elements.
         */
        .def
        (
            py::init([](py::buffer color_buffer, int channels)
            {
              
            // Get the raw pointer to the data
            float* color = return_float_ptr(color_buffer);

            // Return the Image
            return pic::Image(color, channels); 
            }),
            py::return_value_policy::take_ownership,
            "Image is a constructor which initializes an image defined by"
            "the passed color_buffer and number of channels.",
            py::arg("color"), py::arg("channels")
        )

        /**
         * @brief Image is a constructor which initializes an image defined by
         *        the input properties.
         * @param frames is the number of temporal pixels.
         * @param width is the number of horizontal pixels.
         * @param height is the number of vertical pixels.
         * @param channels is the number of color channels.
         * @param data is a buffer of size frames * width * height * channels.
         *             If it is empty (set to NULL) a new buffer will be created.
         */
        .def
        (
            py::init([](int frames, int width, int height,
                    int channels, py::buffer data_buffer)
            {

            // Get the raw pointer to the data
            float* data = return_float_ptr(data_buffer);
            
            //Return a new instance of Image
            return pic::Image(frames, width, height, channels, data); 
            }),
            py::return_value_policy::take_ownership,
            py::arg("frames"), py::arg("width"), py::arg("height"),
            py::arg("channels"), py::arg("data")
        )

        // endregion Constructors

        // region Methods

        /**
         * @brief scaleCosine multiplies the current image by the vertical cosine
         *        assuming a longitude-latitude image.
         */
        .def
        (
            "scaleCosine",
            ([](pic::Image *this_img)
            {
            // Check if the image is empty
            if ( this_img->isValid() )
                return this_img->scaleCosine();
            
            else
                throw std::runtime_error("Can't perfom scaleCosine," 
                                        " the image is empty"); 
            }),
            "scaleCosine multiplies the current image by the"
            " vertical cosine assuming a longitude-latitude image."
        )

        /**
         * @brief FlipH flips horizontally the current image.
         */
        .def
        (
            "flipH",
            ([](pic::Image *this_img)
            {
            // Check if the image is empty
            if ( this_img->isValid() )
                return this_img->flipH();
            
            else
                throw std::runtime_error("Can't perfom flipH," 
                                        " the image is empty"); 
            }),
            py::return_value_policy::take_ownership,
            "FlipH flips horizontally the current image."
        )
        
        /**
         * @brief FlipV flips vertically the current image.
         */
        .def
        (
            "flipV",
            ([](pic::Image *this_img)
            {
            // Check if the image is empty
            if ( this_img->isValid() )
                return this_img->flipV();
            
            else
                throw std::runtime_error("Can't perfom flipV," 
                                        " the image is empty"); 
            }),
            py::return_value_policy::take_ownership,
            "FlipV flips vertically the current image."
        )

        /**
         * @brief flipHV flips horizontally and vertically the current image.
         */
        .def("flipHV", ([](pic::Image *this_img)
                        {
            // Check if the image is empty
            if ( this_img->isValid() )
                return this_img->flipHV();
            
            else
                throw std::runtime_error("Can't perfom flipHV," 
                                        " the image is empty"); }),
            py::return_value_policy::take_ownership,
             "flipHV flips horizontally and vertically the current image.")

        /**
         * @brief flipVH flips vertically and horizontally the current image.
         */
        .def("flipVH", ([](pic::Image *this_img)
                        {
            // Check if the image is empty
            if ( this_img->isValid() )
                return this_img->flipVH();
            
            else
                throw std::runtime_error("Can't perfom flipVH," 
                                        " the image is empty"); }),
            py::return_value_policy::take_ownership,
             "flipVH flips vertically and horizontally the current image.")

        /**
         * @brief rotate90CCW rotates 90 degrees counter-clockwise the current image.
         */
        .def
        (
            "rotate90CCW", 
            ([](pic::Image *this_img)
            {
            // Check if the image is empty
            if ( this_img->isValid() )
                return this_img->rotate90CCW();
            
            else
                throw std::runtime_error("Can't perfom rotate90CCW," 
                                        " the image is empty");
            }), 
            "rotate90CCW rotates 90 degrees counter-clockwise the"
            " current image."
            )

        /**
         * @brief rotate90CW rotates 90 degrees clockwise the current image.
         */
        .def
        (
            "rotate90CW", 
            ([](pic::Image *this_img)
            {
            // Check if the image is empty
            if ( this_img->isValid() )
                return this_img->rotate90CW();
            
            else
                throw std::runtime_error("Can't perfom rotate90CW," 
                                        " the image is empty"); 
            }),
            "rotate90CW rotates 90 degrees clockwise the current image.")

        /**
         * @brief getDiagonalSize returns the image's diagonal. 
         * @return
         */
        .def
        (
            "getDiagonalSize", 
            ([](pic::Image *this_img)
            {
            // Check if the image is empty
            if ( this_img->isValid() )
                return this_img->getDiagonalSize();
            
            else
                throw std::runtime_error("Can't perfom getDiagonalSize," 
                                        " the image is empty"); 
            }),
            py::return_value_policy::take_ownership,
            "getDiagonalSize returns the image's diagonal.")

        /**
         * @brief isValid checks if the current image is valid, which means if they
         *        have an allocated buffer or not.
         * @return This function return true if the current Image is allocated,
         *         otherwise false.
         */
        .def("isValid", &pic::Image::isValid,
            "isValid checks if the current image is valid, which means"
            " if they have an allocated buffer or not.")

        /**
         * @brief isSimilarType checks if the current image is similar to img;
         *        i.e. if they have the same width, height, frames, and channels.
         * @param img is an input image
         * @return This function returns true if the two images are similar,
         *         otherwise false.
         */
        .def
        (
            "isSimilarType", 
            ([](pic::Image *this_img, pic::Image *other_img)
            {
            // Check if one of the images is empty
            if ( this_img->isValid() && other_img->isValid() )
                return this_img->isSimilarType(other_img);
            else
                throw std::runtime_error("Can't perfom isSimilarType," 
                                        " one of the images is empty"); 
            }),
            py::return_value_policy::take_ownership,
            "isSimilarType checks if the current image is similar to img;"
            " i.e. if they have the same width, height, frames, and channels.",
            py::arg("img"))

        /**
         * @brief minimum is the minimum operator for Image.
         * @param img is a and Image and the operand. This
         *        and the current Image need to have the same width,
         *        height, and color channels.
         */
        .def("minimum", &pic::Image::minimum,
             "minimum is the minimum operator for Image.",
             py::arg("img"))

        /**
         * @brief maximum is the maximum operator for Image.
         * @param img is a and Image and the operand. This
         * and the current Image need to have the same width,
         * height, and color channels.
         */
        .def("maximum", &pic::Image::maximum,
             "maximum is the maximum operator for Image.",
             py::arg("img"))

        /**
         * @brief getFullBox computes a full BBox for this image.
         * @return This function returns a full BBox for this image.
         */
        .def("getFullBox", &pic::Image::getFullBox,
            py::return_value_policy::take_ownership,
            "getFullBox computes a full BBox for this image.")
        
        /**
         * @brief getMaxVal computes the maximum value for the current Image.
         * @param box is the bounding box where to compute the function
         * @param ret is an array where the function computations are stored. If it
         *        is set to NULL an array will be allocated.
         * @return This function returns an array where the function computations
         *         are stored.
         */
        .def
        (
            "getMaxVal", 
            ([](pic::Image *this_img, pic::BBox *box)
            {
                        
            // Get the raw pointer to the data
            float* ret = NULL;

            // Call the function
            float* max_val = this_img->getMaxVal(box, ret);

            // Return the NumPy array to Python
            return py::array_t<float>(this_img->channels, max_val);
            }),
            py::return_value_policy::take_ownership,
            "getMaxVal computes the maximum value for the current Image.",
            py::arg("box")
        )

        /**
         * @brief getMaxVal computes the maximum value for the current Image.
         *        The function will compute on the entire image.
         * @return This function returns an array where the function computations
         *         are stored.
         */
        .def
        (
            "getMaxVal", 
            ([](pic::Image *this_img)
            {
            
            // Call the function
            float* max_val = this_img->getMaxVal(NULL, NULL);

            // Return the NumPy array to Python
            return py::array_t<float>(this_img->channels, max_val);
            }),
            py::return_value_policy::take_ownership,
            "getMaxVal computes the maximum value for the current Image.\nThe function will compute on the entire image."
        )

        /**
         * @brief getMinVal computes the minimum value for the current Image.
         * @param box is the bounding box where to compute the function. If it
         * is set to NULL the function will be computed on the entire image.
         * @return This function returns an array where the function computations
         * are stored.
         */
        .def
        (
            "getMinVal", 
            ([](pic::Image *this_img, pic::BBox *box)
            {
            // Call the function
            float* min_val = this_img->getMinVal(box, NULL);

            // Return the NumPy array to Python
            return py::array_t<float>(this_img->channels, min_val);
            }),
            py::return_value_policy::take_ownership,
            "getMinVal computes the minimum value for the current Image.",
            py::arg("box")
        )

        /**
         * @brief getMinVal computes the minimum value for the current Image.
         *        are stored.
         *        The function will compute on the entire image.
         */
        .def
        (
            "getMinVal", 
            ([](pic::Image *this_img)
            {
            
            // Call the function
            float* min_val = this_img->getMinVal(NULL, NULL);

            // Return the NumPy array to Python
            return py::array_t<float>(this_img->channels, min_val);
            }),
            py::return_value_policy::take_ownership,
            "getMinVal computes the minimum value for the current Image.\nThe function will compute on the entire image."
        )

        /**
         * @brief getLogMeanVal computes the log mean for the current Image.
         * @param box is the bounding box where to compute the function. If it
         * is set to NULL the function will be computed on the entire image.
         * @param ret is an array where the function computations are stored. If it
         * is set to NULL an array will be allocated.
         * @return This function returns an array where the function computations
         * are stored.
         */
        .def
        (
            "getLogMeanVal", 
            ([](pic::Image *this_img, pic::BBox *box)
            {
            // Call the function
            float* log_mean_val = this_img->getLogMeanVal(box, NULL);

            // Return the NumPy array to Python
            return py::array_t<float>( this_img->channels, log_mean_val); 
            }),
            py::return_value_policy::take_ownership,
            "getLogMeanVal computes the log mean for the current Image.",
            py::arg("box")
        )

                /**
         * @brief getLogMeanVal computes the log mean for the current Image.
         *        The function will be computed on the entire image.
         * @return This function returns an array where the function computations
         * are stored.
         */
        .def
        (
            "getLogMeanVal", 
            ([](pic::Image *this_img)
            {
            // Call the function
            float* log_mean_val = this_img->getLogMeanVal(NULL, NULL);

            // Return the NumPy array to Python
            return py::array_t<float>( this_img->channels, log_mean_val); 
            }),
            py::return_value_policy::take_ownership,
            "getLogMeanVal computes the log mean for the current Image."
        )

        /**
         * @brief getSumVal sums values for the current Image.
         * @param box is the bounding box where to compute the function. If it
         * is set to NULL the function will be computed on the entire image.
         * @return This function returns an array where the function computations
         * are stored.
         */
        .def
        (
            "getSumVal", 
            ([](pic::Image *this_img, pic::BBox *box)
            {
            // Call the function
            float* sum_val = this_img->getSumVal(box, NULL);

            // Return the NumPy array to Python
            return py::array_t<float>( this_img->channels, sum_val);  
            }),
            py::return_value_policy::take_ownership,
            "getSumVal sums values for the current Image.",
            py::arg("box")
        )

        /**
         * @brief getSumVal sums values for the current Image.
         *        The function will be computed on the entire image.
         * @return This function returns an array where the function computations
         * are stored.
         */
        .def
        (
            "getSumVal", 
            ([](pic::Image *this_img)
            {
            // Call the function
            float* sum_val = this_img->getSumVal(NULL, NULL);

            // Return the NumPy array to Python
            return py::array_t<float>( this_img->channels, sum_val);  
            }),
            py::return_value_policy::take_ownership,
            "getSumVal sums values for the current Image."
        )

        /**
         * @brief getMeanVal computes the mean for the current Image.
         * @param box is the bounding box where to compute the function. If it
         * is set to NULL the function will be computed on the entire image.
         * @return This function returns an array where the function computations
         * are stored.
         */
        .def
        (
            "getMeanVal", 
            ([](pic::Image *this_img, pic::BBox *box)
            {
            // Call the function
            float* mean_val = this_img->getMeanVal(box, NULL);

            // Return the NumPy array to Python
            return py::array_t<float>( this_img->channels, mean_val); 
            }),
            py::return_value_policy::take_ownership,
            "getMeanVal computes the mean for the current Image.",
            py::arg("box")
        )

        /**
         * @brief getMeanVal computes the mean for the current Image.
         *        The function will be computed on the entire image.
         * @return This function returns an array where the function computations
         * are stored.
         */
        .def
        (
            "getMeanVal", 
            ([](pic::Image *this_img)
            {
            // Call the function
            float* mean_val = this_img->getMeanVal(NULL, NULL);

            // Return the NumPy array to Python
            return py::array_t<float>( this_img->channels, mean_val); 
            }),
            py::return_value_policy::take_ownership,
            "getMeanVal computes the mean for the current Image."
        )

        /**
         * @brief getMomentsVal computes the moments at pixel (x0, y0).
         * @param x0 is the horizontal coordinate.
         * @param y0 is the vertical coordinate.
         * @param radius is the radius of the patch.
         * @return This function returns an array where the function computations
         * are stored.
         */
        .def
        (
            "getMomentsVal", 
            ([](pic::Image *this_img, int x0, int y0,
                int radius)
            {
            // Call the function
            float* moments_val = this_img->getMomentsVal(x0, y0, radius, NULL);

            // Return the NumPy array to Python
            return py::array_t<float>( ( this_img->channels << 1 ), moments_val);  
            }),
            py::return_value_policy::take_ownership,
            "getMomentsVal computes the moments at pixel (x0, y0).",
            py::arg("x0"), py::arg("y0"), 
            py::arg("radius")
        )

        /**
         * @brief getVarianceVal computes the variance for the current Image.
         * @param meanVal is the array where the values are stored
         * @param box is the bounding box where to compute the function. If it
         * is set to NULL the function will be computed on the entire image.
         * @return This function returns an array where the function computations
         * are stored.
         */
        .def
        (
            "getVarianceVal", 
            ([](pic::Image *this_img, py::buffer mean_val_buffer,
                pic::BBox *box)
            {
            // Get the raw pointer for mean_val
            float* mean_val = return_float_ptr(mean_val_buffer);

            // Call the function
            float* variance_val = this_img->getVarianceVal(mean_val, box, NULL);

            // Return the NumPy array to Python
            return py::array_t<float>( this_img->channels, variance_val); 
            }),
            py::return_value_policy::take_ownership,
            "getVarianceVal computes the variance for the current Image.",
            py::arg("meanVal"), py::arg("box")
        )

        /**
         * @brief getCovMtxVal computes the convariance matrix for the current Image.
         * @param meanVal is the array containing the values.
         * @param box is the bounding box where to compute the function. If it
         * is set to NULL the function will be computed on the entire image.
         * @return This function returns an array where the function computations
         * are stored.
         */
        .def
        (
            "getCovMtxVal", 
            ([](pic::Image *this_img, py::buffer mean_val_buffer, pic::BBox *box)
            {
            // Get the raw pointer to the data
            float* mean_val = return_float_ptr(mean_val_buffer);

            // Call the function
            float* cov_mtx_val = this_img->getCovMtxVal(mean_val, box, NULL);

            // Return the NumPy array to Python
            return py::array_t<float>( (this_img->channels * this_img->channels), 
                                     cov_mtx_val);  
            }),
            py::return_value_policy::take_ownership,
            "getVarianceVal computes the variance for the current Image.",
            py::arg("meanVal"), py::arg("box")
        )

        /**
         * @brief getPercentileVal computes the n-th value given a percentile.
         * @param percentile is the percentile.
         * @param box is the bounding box where to compute the function. If it
         * is set to NULL the function will be computed on the entire image.
         * @return This function returns an array where the function computations
         * are stored.
         */
        .def
        (
            "getPercentileVal", 
            ([](pic::Image *this_img, float percentile, 
                pic::BBox *box)
            {
            // return the function
            return this_img->getPercentileVal(percentile, box, NULL); 
            }),
            py::return_value_policy::take_ownership,
            "getPercentileVal computes the median value value given a percentile.",
            py::arg("percentile"), py::arg("box")
        )

        /**
         * @brief getMedVal computes the median value value given a percentile.
         * @param box is the bounding box where to compute the function. If it
         * is set to NULL the function will be computed on the entire image.
         * @param percentile is the percentile.
         * @return This function returns an array where the function computations
         * are stored.
         */
        .def
        (
            "getMedVal", 
            ([](pic::Image *this_img, pic::BBox *box)
            {
            // Call the function
            float* med_val = this_img->getMedVal(box, NULL);

            // Return the NumPy array to Python
            return py::array_t<float>( ( this_img->channels << 1 ), 
                                     med_val); 
            }),
            py::return_value_policy::take_ownership,
            "getMedVal",
            py::arg("box")
        )

        /**
         * @brief getDynamicRange computes the dynamic range of the image.
         * @param bRobust is a value that enables robust computation of the dynamic range using percentile.
         * @param percentile is the percentile value used when computing the dynamic range in a robust way.
         * @return
         */
        .def("getDynamicRange", &pic::Image::getDynamicRange,
            py::return_value_policy::take_ownership,
            "getDynamicRange computes the dynamic range of the image.",
            py::arg("bRobust"), py::arg("percentile"))

        /**
         * @brief getColorSamples computed the colors of the image.
         * @param samples is the arrays if samples to check.
         * @param percentage is the percentage value used when computing the color samples.
         * @return
         */
        .def
        (
            "getColorSamples", 
            ([](pic::Image *this_img, py::buffer samples_buffer, 
                int &nSamples, float percentage)
            {
            // Get the raw pointer to the data
            float *samples = return_float_ptr(samples_buffer);

            // Call the function
            samples = this_img->getColorSamples(samples,
                                                                         nSamples, percentage);

            // Return the NumPy array to Python
            int size = nSamples * this_img->channels;
            return py::array_t<float>(size, samples);
            }),
            "getColorSamples",
            py::return_value_policy::take_ownership,
            py::arg("samples"), py::arg("nSamples"), 
            py::arg("percentage")
        )

        /**
         * @brief blend apply the blending to the image.
         * @param img is the image used to blend.
         * @param weight is the weight used to blend image.
         */
        .def("blend", &pic::Image::blend,
             "blend", 
             py::arg("img"), py::arg("weight"))

        /**
         * @brief size computes the number of values.
         * @return This function returns the number of values of the entire image.
         */
        .def("size", &pic::Image::size,
            py::return_value_policy::take_ownership,
            "size computes the number of values.")

        /**
         * @brief size computes the number of values.
         * @return This function returns the number of values of a frame.
         */
        .def("sizeFrame", &pic::Image::sizeFrame, 
            py::return_value_policy::take_ownership,
            "sizeFrame")

        /**
         * @brief nPixels computes the number of pixels.
         * @return This function returns the number of pixels.
         */
        .def("nPixels", &pic::Image::nPixels,
            "nPixels computes the number of pixels",
            py::return_value_policy::take_ownership)

        /**
         * @brief checkCoordinates checks (x, y, z) coordinates) if they are valid or not.
         * @param x is the horizontal coordinate.
         * @param y is the vertical coordinate.
         * @param z is the temporal coordinate.
         * @return This function returns true if the coordinates are inside the bounding
         *         box of the Image.
         */
        .def("checkCoordinates", &pic::Image::checkCoordinates, 
            "checkCoordinates checks (x, y, z) coordinates)"
            "if they are valid or not.",
            py::return_value_policy::take_ownership,
            py::arg("x"), py::arg("y"), 
            py::arg("z") = 0)

        /**
         * @brief convertFromMask converts a boolean mask into an Image. true is mapped
         *        to 1.0f, and false is mapped to 0.0f.
         * @param mask is a buffer of boolean values with (width * height) elements.
         * @param width is the horizontal number of pixels.
         * @param height is the vertical number of pixels.
         */
        .def
        (
            "convertFromMask", 
            ([](pic::Image *this_img, py::buffer mask_buffer, 
                int width, int height)
            {
            // Get the raw pointer for mask
            bool* mask = return_bool_ptr(mask_buffer);

            // Call the function
            return this_img->convertFromMask( mask, width, height); 
            }),
            py::return_value_policy::take_ownership,
            "convertFromMask converts a boolean mask into an Image."
            "true is mapped to 1.0f, and false is mapped to 0.0f.",
            py::arg("mask"), py::arg("width"), 
            py::arg("height")
        )

        /**
         * @brief convertToMask converts an Image into a boolean mask.
         * @param color
         * @param threshold
         * @param cmp
         * @param mask is a buffer of boolean values with (width * height) elements.
         * @return
         */
        .def
        (
            "convertToMask", 
            ([](pic::Image *this_img, py::buffer color_buffer, 
                float threshold = 0.25f, bool cmp = true)
            {
            // Get the raw pointer for color
            float *color = return_float_ptr(color_buffer);

            // Call the function
            bool *mask = this_img->convertToMask(color, threshold, cmp, NULL);
            int size = this_img->width * this_img->height;

            // Return the NumPy array to Python
            return py::array_t<bool, py::array::c_style>(size, mask);
            }),
            py::return_value_policy::take_ownership,
            "convertToMask converts an Image into a boolean mask.", 
            py::arg("color") = NULL, py::arg("threshold") = 0.25f, 
            py::arg("cmp") = true)

        /**
         * @brief Read opens an Image from a file on the disk.
         * @param nameFile is the file name.
         * @param typeLoad is an option for LDR images only:
         * LT_NOR means that the input image values will be normalized in [0,1].
         * LT_NOR_GAMMA means that the input image values will be normalized in [0,1], and
         * gamma correction 2.2 will be removed.
         * LT_NONE means that image values are not modified.
         *
         * The default is LT_NOR_GAMMA assuming that
         * we are storing normalized and linearized values in Image.
         *
         * @return This returns true if the reading succeeds, false otherwise.
         */
        .def("Read", &pic::Image::Read, 
            "Read opens an Image from a file on the disk.", 
            py::return_value_policy::take_ownership,
            py::arg("nameFile"), 
            py::arg("typeLoad") = pic::LDR_type::LT_NOR_GAMMA)

        /**
         * @brief Write saves an Image into a file on the disk.
         * @param nameFile is the file name.
         * @param typeWrite is an option for LDR images only:
         * LT_NOR means that Image ha normalized values and the output image
         * values will be multiplied by 255 to have values in [0,255].
         * LT_NOR_GAMMA means that Image ha normalized and linearized values. The output image
         * values will be gamma corrected (2.2) and multiplied by 255 to have values in [0,255].
         * LT_NONE means that Image values are the same of the output.
         *
         * The default is LT_NOR_GAMMA assuming that
         * we are storing normalized and linearized values in Image.
         *
         * @param writerCounter is the frame that we want to write on the disk in the case Image is a video.
         * The default writerCounter value is 0.
         * @return This returns true if the writing succeeds, false otherwise.
         */
        .def("Write", &pic::Image::Write,
            "Write saves an Image into a file on the disk.",
            py::return_value_policy::take_ownership, 
            py::arg("nameFile"), 
            py::arg("typeWrite") = pic::LT_NOR_GAMMA, 
            py::arg("writeCounter") = 0)

        /**
         * @brief clamp set data values in the range [a,b]
         * @param a the minimum value.
         * @param b the maximum value.
         */
        .def("clamp", &pic::Image::clamp,
            "clamp set data values in the range [a,b]",
            py::arg("a"), py::arg("b"))

        /**
         * @brief removeSpecials removes NaN and +/-Inf values and sets
         * them to 0.0f.
         */
        .def("removeSpecials", &pic::Image::removeSpecials,
            "removeSpecials removes NaN and +/-Inf values and sets them to 0.0f.")

        // endregion Methods

        // region Special-Methods

        /**
         * @brief defines the __repr__ python method
         *        returning a string stating if the image
         *        is full (has associated a read image) or
         *        empty (has invalid field values).
         */
        .def
        (
            "__repr__", 
            ([](pic::Image *this_img)
            {   
                std::string ret_str;
                if (!this_img->isValid())
                {
                    ret_str = "This is an empty image.";
                }
                else
                {
                    ret_str = "This is a full image.";
                }
                return ret_str;
            })
        )

        .def(py::self += float())
        .def(py::self += py::self)
        .def(py::self + py::self)
        .def(py::self + float())
        .def(py::self *= float())
        .def(py::self *= py::self)
        .def(py::self * float())
        .def(py::self * py::self)
        .def(py::self -= float())
        .def(py::self -= py::self)
        .def(py::self - float())
        .def(py::self - py::self)
        .def(py::self /= float())
        .def(py::self /= py::self)
        .def(py::self / float())
        .def(py::self / py::self)

        // endregion Special-Methods

        // region Args

        .def_readonly("width", &pic::Image::width)
        .def_readonly("height", &pic::Image::height)
        .def_readonly("channels", &pic::Image::channels)
        .def_readonly("frames", &pic::Image::frames)
        .def_readonly("depth", &pic::Image::depth)
        .def_readonly("alpha", &pic::Image::alpha)
        .def_readonly("tstride", &pic::Image::tstride)
        .def_readonly("ystride", &pic::Image::ystride)
        .def_readonly("xstride", &pic::Image::xstride)
        .def_readonly("widthf", &pic::Image::widthf)
        .def_readonly("width1f", &pic::Image::width1f)
        .def_readonly("heightf", &pic::Image::heightf)
        .def_readonly("channelsf", &pic::Image::channelsf)
        .def_readonly("framesf", &pic::Image::framesf)
        .def_readonly("frames1f", &pic::Image::frames1f)
        .def_readonly("nameFile", &pic::Image::nameFile);

        // endregionn Args

    // regione Custom_Functions
    

    /**
     * @brief getData returns the data array containing the raw image.
     * @return Returns a numpy float array containing the raw image.
    */
    m.def(
        "getData",
        ([](pic::Image *this_img)
        {   

            // Return the NumPy array to Python
            return py::array_t<float>((this_img->size()), this_img->data);
        }),
        "get the img buffer",
        py::return_value_policy::take_ownership
        );
}
