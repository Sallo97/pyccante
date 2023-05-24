#include "py_image.h"

void init_Image(pybind11::module_ &m)
{
    py::class_<pic::Image>(m, "Image")

        // region Constructors

        .def(py::init<>(),
            "Makes an empty image",
            py::return_value_policy::take_ownership)

        .def(py::init<std::string &, pic::LDR_type>(),
            py::return_value_policy::take_ownership,
            "Image loads an Image from a file on the disk.",
            py::arg("nameFile"), py::arg("typeLoad"))

        .def(py::init<int, int, int>(),
             "Image creates an Image with a given size.",
            py::return_value_policy::take_ownership,
            py::arg("width"), py::arg("height"),
            py::arg("channels"))

        .def(py::init<pic::Image *, bool>(),
            "Image embeds an existing image in the new image.",
            py::return_value_policy::take_ownership,
            py::arg("imgIn"), py::arg("deepCopy"))

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
            " the input properties.",
            py::arg("color"), py::arg("channels")
        )

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

        // endregion

        // region Functions

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
            "FlipH flips horizontally the current image."
        )

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
            "FlipV flips vertically the current image."
        )

        .def("flipHV", ([](pic::Image *this_img)
                        {
            // Check if the image is empty
            if ( this_img->isValid() )
                return this_img->flipHV();
            
            else
                throw std::runtime_error("Can't perfom flipHV," 
                                        " the image is empty"); }),
             py::return_value_policy::reference,
             "flipHV flips horizontally and vertically the current image.")

        .def("flipVH", ([](pic::Image *this_img)
                        {
            // Check if the image is empty
            if ( this_img->isValid() )
                return this_img->flipVH();
            
            else
                throw std::runtime_error("Can't perfom flipVH," 
                                        " the image is empty"); }),
             py::return_value_policy::reference,
             "flipVH flips vertically and horizontally the current image.")

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
            "getDiagonalSize")

        .def("isValid", &pic::Image::isValid,
            "isValid checks if the current image is valid, which means"
            " if they have an allocated buffer or not.")

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

        .def("minimum", &pic::Image::minimum,
             "minimum is the minimum operator for Image.",
             py::arg("img"))

        .def("maximum", &pic::Image::maximum,
             "maximum is the maximum operator for Image.",
             py::arg("img"))

        .def("getFullBox", &pic::Image::getFullBox,
            py::return_value_policy::take_ownership,
            "getFullBox computes a full BBox for this image.")

        .def
        (
            "getMaxVal", 
            ([](pic::Image *this_img, pic::BBox *box, py::buffer ret_buffer)
            {
                        
            // Get the raw pointer to the data
            float* ret = return_float_ptr(ret_buffer);

            // Call the function
            float* max_val = this_img->getMaxVal(box, ret);

            // Return the NumPy array to Python
            return return_numpy_array(max_val); 
            }),
            py::return_value_policy::take_ownership,
            "getMaxVal computes the maximum value for the current Image.",
            py::arg("box"), py::arg("ret")
        )

        .def
        (
            "getMinVal", 
            ([](pic::Image *this_img, pic::BBox *box,
                py::buffer ret_buffer)
            {

            // Get the raw pointer to the data
            float* ret = return_float_ptr(ret_buffer);

            // Call the function
            float* min_val = this_img->getMinVal(box, ret);

            // Return the NumPy array to Python
            return return_numpy_array(min_val); 
            }),
            py::return_value_policy::take_ownership,
            "getMinVal computes the minimum value for the current Image.",
            py::arg("box"), py::arg("ret"))

        .def
        (
            "getLogMeanVal", 
            ([](pic::Image *this_img, pic::BBox *box, 
                py::buffer ret_buffer)
            {
                  
            // Get the raw pointer to the data
            float* ret = return_float_ptr(ret_buffer);

            // Call the function
            float* log_mean_val = this_img->getLogMeanVal(box, ret);

            // Return the NumPy array to Python
            return return_numpy_array(log_mean_val); 
            }),
            py::return_value_policy::take_ownership,
            "getLogMeanVal computes the log mean for the current Image.",
            py::arg("box"), py::arg("ret"))

        .def
        (
            "getSumVal", 
            ([](pic::Image *this_img, pic::BBox *box, 
                py::buffer ret_buffer)
            {
            
            // Get the raw pointer to the data
            float* ret = return_float_ptr(ret_buffer);

            // Call the function
            float* sum_val = this_img->getSumVal(box, ret);

            // Return the NumPy array to Python
            return return_numpy_array(sum_val); 
            }),
            py::return_value_policy::reference,
            "getSumVal sums values for the current Image.",
            py::arg("box"), py::arg("ret"))

        .def
        (
            "getMeanVal", 
            ([](pic::Image *this_img, pic::BBox *box, 
                py::buffer ret_buffer)
            {
            
            // Get the raw pointer to the data
            float* ret = return_float_ptr(ret_buffer);

            // Call the function
            float* mean_val = this_img->getMeanVal(box, ret);

            // Return the NumPy array to Python
            return return_numpy_array(mean_val); 
            }),
            py::return_value_policy::take_ownership,
            "getMeanVal computes the mean for the current Image.",
            py::arg("box"), py::arg("ret"))

        .def
        (
            "getMomentsVal", 
            ([](pic::Image *this_img, int x0, int y0,
                int radius, py::buffer ret_buffer)
            {
            // Get the raw pointer to the data
            float* ret = return_float_ptr(ret_buffer);

            // Call the function
            float* moments_val = this_img->getMomentsVal(x0, y0, radius, ret);

            // Return the NumPy array to Python
            return return_numpy_array(moments_val); 
            }),
            py::return_value_policy::take_ownership,
            "getMomentsVal computes the moments at pixel (x0, y0).",
            py::arg("x0"), py::arg("y0"), 
            py::arg("radius"),py::arg("ret")
        )

        .def
        (
            "getVarianceVal", 
            ([](pic::Image *this_img, py::buffer mean_val_buffer,
                pic::BBox *box, py::buffer ret_buffer)
            {
            // Get the raw pointer for ret
            float* ret = return_float_ptr(ret_buffer);

            // Get the raw pointer for mean_val
            float* mean_val = return_float_ptr(mean_val_buffer);

            // Call the function
            float* variance_val = this_img->getVarianceVal(mean_val, box, ret);

            // Return the NumPy array to Python
            return return_numpy_array(variance_val); 
            }),
            py::return_value_policy::take_ownership,
            "getVarianceVal computes the variance for the current Image.",
            py::arg("meanVal"), py::arg("box"), 
            py::arg("ret")
        )

        .def
        (
            "getCovMtxVal", 
            ([](pic::Image *this_img, py::buffer mean_val_buffer, pic::BBox *box, py::buffer ret_buffer)
            {
            // Get the raw pointer to the data
            float* ret = return_float_ptr(ret_buffer);

            // Get the raw pointer to the data
            float* mean_val = return_float_ptr(mean_val_buffer);

            // Call the function
            float* cov_mtx_val = this_img->getCovMtxVal(mean_val, box, ret);

            // Return the NumPy array to Python
            return return_numpy_array(cov_mtx_val); 
            }),
            py::return_value_policy::take_ownership,
            "getVarianceVal computes the variance for the current Image.",
            py::arg("meanVal"), py::arg("box"),
            py::arg("ret")
        )

        .def
        (
            "getPercentileVal", 
            ([](pic::Image *this_img, float percentile, 
                pic::BBox *box, py::buffer ret_buffer)
            {
            // Get the raw pointer to the data
            float* ret = return_float_ptr(ret_buffer);

            // return the function
            return this_img->getPercentileVal(percentile, box, ret); 
            }),
            py::return_value_policy::take_ownership,
            "getPercentileVal computes the median value value given a percentile.",
            py::arg("percentile"), py::arg("box"), py::arg("ret")
        )

        .def
        (
            "getMedVal", 
            ([](pic::Image *this_img, pic::BBox *box, 
                py::buffer ret_buffer)
            {
            // Get the raw pointer to the data
            float* ret = return_float_ptr(ret_buffer);

            // Call the function
            float* med_val = this_img->getMedVal(box, ret);

            // Return the NumPy array to Python
            return return_numpy_array(med_val); 
            }),
            py::return_value_policy::take_ownership,
            "getMedVal",
            py::arg("box"), py::arg("ret")
        )

        .def("getDynamicRange", &pic::Image::getDynamicRange,
            py::return_value_policy::take_ownership,
            "getDynamicRange computes the dynamic range of the image.",
            py::arg("bRobust"), py::arg("percentile"))

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

        .def("blend", &pic::Image::blend, "blend", py::arg("img"), py::arg("weight"))

        .def("size", &pic::Image::size,
            py::return_value_policy::take_ownership,
            "size computes the number of values.")

        .def("sizeFrame", &pic::Image::sizeFrame, 
            py::return_value_policy::take_ownership,
            "sizeFrame")

        .def("nPixels", &pic::Image::nPixels,
            "nPixels computes the number of pixels",
            py::return_value_policy::take_ownership)

        .def("checkCoordinates", &pic::Image::checkCoordinates, 
            "checkCoordinates checks (x, y, z) coordinates)"
            "if they are valid or not.",
            py::return_value_policy::take_ownership,
            py::arg("x"), py::arg("y"), 
            py::arg("z") = 0)

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

        .def("Read", &pic::Image::Read, 
            "Read opens an Image from a file on the disk.", 
            py::return_value_policy::take_ownership,
            py::arg("nameFile"), 
            py::arg("typeLoad") = pic::LDR_type::LT_NOR_GAMMA)

        .def("Write", &pic::Image::Write,
            "Write saves an Image into a file on the disk.",
            py::return_value_policy::take_ownership, 
            py::arg("nameFile"), 
            py::arg("typeWrite") = pic::LT_NOR_GAMMA, 
            py::arg("writeCounter") = 0)

        .def("clone", &pic::Image::clone,
            py::return_value_policy::take_ownership, 
            "Clone creates a deep copy of the calling instance.")

        // endregion

        // region base_func

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

        // endregion

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

    // endregion
}
