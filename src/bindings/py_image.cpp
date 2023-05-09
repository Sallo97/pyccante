#include "py_image.h"

namespace py = pybind11;
using namespace py::literals;

void init_Image(pybind11::module_& m)
{
    // region Constructors

    py::class_<pic::Image>(m, "Image")
        .def(py::init<> ())

        .def(py::init<std::string &, pic::LDR_type>(),
            "Image loads an Image from a file on the disk.",
            py::arg("nameFile"), py::arg("typeLoad"))
        
        .def(py::init<int, int, int>(),
            "Image creates an Image with a given size.",
            py::arg("width"), py::arg("height"),
            py::arg("channels"))

        
        .def(py::init( [](py::buffer color_buffer, int channels) {
            // Get the buffer information
            py::buffer_info info = color_buffer.request();

            // Check if the buffer is type float
            if (info.format != py::format_descriptor<float>::format())
                throw std::runtime_error("Incompatible buffer format, must be of float values.");
            
            // Get the raw pointer to the data
            float* color = static_cast<float*>(info.ptr);

            // Return the Image
            return new pic::Image(color, channels);
            }),
            "Image is a constructor which initializes an image defined by"
            " the input properties.",
            py::arg("color"), py::arg("channels")) 
        
        .def(py::init( []( int frames, int width, int height,
            int channels, py::buffer data_buffer) {
            // Get the buffer information
            py::buffer_info info = data_buffer.request();

            if(info.format != py::format_descriptor<float>::format())
                throw std::runtime_error("Incompatible buffer format, must be of float values.");            

            // Get the raw pointer to the data
            float* data = static_cast<float*>(info.ptr);
            
            //Return a new instance of Image
            return new pic::Image(frames, width, height, channels, data);
            }),
            py::arg("frames"), py::arg("width"), py::arg("height"),
            py::arg("channels"), py::arg("data"))

    // endregion

    //region Functions

        .def("allocate", &pic::Image::allocate,
            "allocate allocates memory for the pixel buffer.",
            py::arg("width"), py::arg("height"), 
            py::arg("channels"), py::arg("frames"))
        
        .def("allocateAux", &pic::Image::allocateAux,
            "allocateAux computes extra information after allocation;"
            " e.g. strides.")
        
        .def("release", &pic::Image::release,
            "release frees allocated buffers.")
        
        .def("copySubImage", &pic::Image::copySubImage,
            "copySubImage copies imgIn in the current image."
            " The current image is written from (startX, startY).",
            py::arg("imgIn"), py::arg("startX"), py::arg("startY"))
        
        .def("scaleCosine", &pic::Image::scaleCosine,
            "scaleCosine multiplies the current image by the"
            " vertical cosine assuming a longitude-latitude image.")
        
        .def("flipH", &pic::Image::flipH,
            "FlipH flips horizontally the current image.")
        
        .def("flipV", &pic::Image::flipV,
            "FlipV flips vertically the current image.")
        
        .def("flipHV", &pic::Image::flipHV,
            "flipHV flips horizontally and vertically the current image.")
        
        .def("rotate90CCW", &pic::Image::rotate90CCW,
            "rotate90CCW rotates 90 degrees counter-clockwise the" 
            " current image.")
        
        .def("rotate90CW", &pic::Image::rotate90CW,
            "rotate90CW rotates 90 degrees clockwise the current image.")
        
        .def("getDiagonalSize", &pic::Image::getDiagonalSize,
            "getDiagonalSize")
        
        .def("setZero", &pic::Image::setZero,
            "setZero sets data to 0.0f.")
        
        .def("setRand", &pic::Image::setRand,
            "setRand",
            py::arg("seed"))
        
        .def("isValid", &pic::Image::isValid,
            "isValid checks if the current image is valid, which means" 
            " if they have an allocated buffer or not.")
        
        .def("isSimilarType", &pic::Image::isSimilarType,
            "isSimilarType checks if the current image is similar to img;"
            " i.e. if they have the same width, height, frames, and channels.",
            py::arg("img"))
        
        .def("assign", &pic::Image::assign,
            "assign",
            py::arg("imgIn"))
        
        .def("blend", &pic::Image::blend,
            "blend",
            py::arg("img"), py::arg("weight"))
        
        .def("minimum", &pic::Image::minimum,
            "minimum is the minimum operator for Image.",
            py::arg("img"))
        
        .def("maximum", &pic::Image::maximum,
            "maximum is the maximum operator for Image.",
            py::arg("img"))
        
        .def("applyFunction", &pic::Image::applyFunction,
            "applyFunction is an operator that applies"
            " an input function to all values in data."
            )
        
        /* .def("applyFunctionParam", &pic::Image::applyFunctionParam,
            "applyFunction is an operator that applies"
            " an input function to all values in data.",
            py::arg("func")) */
 /*       
        .def("getFullBox", &pic::Image::getFullBox,
            "getFullBox computes a full BBox for this image.")

        .def("getMaxVal",( [](pic::Image* this_img, pic::BBox* box, py::buffer ret_buffer) {
            
            // Get the buffer information
            py::buffer_info info = ret_buffer.request();

            // Check if the buffer is type float
            if ( info.format != py::format_descriptor<float>::format() )
                throw std::runtime_error("Incompatible buffer format," 
                                         "must be of float values.");
            
            // Get the raw pointer to the data
            float* ret = static_cast<float*>(info.ptr);

            // Call the function
            float* max_val = this_img->getMaxVal(box, ret);

            // Create a NumPy array that owns the data of the float* array
            py::array_t<float, py::array::c_style> np_arr({3}, max_val);

            // Return the NumPy array to Python
            return np_arr; 
            }),
            "getMaxVal computes the maximum value for the current Image.",
            py::arg("box"), py::arg("ret"))

        .def("getMinVal",( [](pic::Image* this_img, pic::BBox* box, py::buffer ret_buffer) {
            
            // Get the buffer information
            py::buffer_info info = ret_buffer.request();

            // Check if the buffer is type float
            if ( info.format != py::format_descriptor<float>::format() )
                throw std::runtime_error("Incompatible buffer format," 
                                         "must be of float values.");
            
            // Get the raw pointer to the data
            float* ret = static_cast<float*>(info.ptr);

            // Call the function
            float* max_val = this_img->getMinVal(box, ret);

            // Create a NumPy array that owns the data of the float* array
            py::array_t<float, py::array::c_style> np_arr ({sizeof(max_val) / sizeof(float)}, max_val);

            // Return the NumPy array to Python
            return np_arr; 
            }),
            "getMinVal computes the minimum value for the current Image.",
            py::arg("box"), py::arg("ret"))
        
        .def("getLogMeanVal",( [](pic::Image* this_img, pic::BBox* box, py::buffer ret_buffer) {
            
            // Get the buffer information
            py::buffer_info info = ret_buffer.request();

            // Check if the buffer is type float
            if ( info.format != py::format_descriptor<float>::format() )
                throw std::runtime_error("Incompatible buffer format," 
                                         "must be of float values.");
            
            // Get the raw pointer to the data
            float* ret = static_cast<float*>(info.ptr);

            // Call the function
            float* log_mean_val = this_img->getLogMeanVal(box, ret);

            // Create a NumPy array that owns the data of the float* array
            py::array_t<float, py::array::c_style> np_arr ({sizeof(log_mean_val) / sizeof(float)}, log_mean_val);

            // Return the NumPy array to Python
            return np_arr; 
            }),
            "getLogMeanVal computes the log mean for the current Image.",
            py::arg("box"), py::arg("ret"))
        
        .def("getSumVal",( [](pic::Image* this_img, pic::BBox* box, py::buffer ret_buffer) {
            
            // Get the buffer information
            py::buffer_info info = ret_buffer.request();

            // Check if the buffer is type float
            if ( info.format != py::format_descriptor<float>::format() )
                throw std::runtime_error("Incompatible buffer format," 
                                         "must be of float values.");
            
            // Get the raw pointer to the data
            float* ret = static_cast<float*>(info.ptr);

            // Call the function
            float* sum_val = this_img->getSumVal(box, ret);

            // Create a NumPy array that owns the data of the float* array
            py::array_t<float, py::array::c_style> np_arr ({sizeof(sum_val) / sizeof(float)}, sum_val);

            // Return the NumPy array to Python
            return np_arr; 
            }),
            "getSumVal sums values for the current Image.",
            py::arg("box"), py::arg("ret"))
        
        .def("getMeanVal",( [](pic::Image* this_img, pic::BBox* box, py::buffer ret_buffer) {
            
            // Get the buffer information
            py::buffer_info info = ret_buffer.request();

            // Check if the buffer is type float
            if ( info.format != py::format_descriptor<float>::format() )
                throw std::runtime_error("Incompatible buffer format," 
                                         "must be of float values.");
            
            // Get the raw pointer to the data
            float* ret = static_cast<float*>(info.ptr);

            // Call the function
            float* mean_val = this_img->getMeanVal(box, ret);

            // Create a NumPy array that owns the data of the float* array
            py::array_t<float, py::array::c_style> np_arr ({sizeof(mean_val) / sizeof(float)}, mean_val);

            // Return the NumPy array to Python
            return np_arr; 
            }),
            "getMeanVal computes the mean for the current Image.",
            py::arg("box"), py::arg("ret"))
        
        .def("getMomentsVal", ( [](pic::Image* this_img, int x0, int y0,
                                  int radius, py::buffer ret_buffer)
            {
                // Get the buffer information
                py::buffer_info info = ret_buffer.request();

                // Check if the buffer is type float
                if ( info.format != py::format_descriptor<float>::format() )
                    throw std::runtime_error("Incompatible buffer format," 
                                         "must be of float values.");
            
                // Get the raw pointer to the data
                float* ret = static_cast<float*>(info.ptr);

                // Call the function
                float* moments_val = this_img->getMomentsVal(x0, y0, radius, ret);

                // Create a NumPy array that owns the data of the float* array
                py::array_t<float, py::array::c_style> np_arr ({sizeof(moments_val) / sizeof(float)}, moments_val);

                // Return the NumPy array to Python
                return np_arr; 
            }),
            "getMomentsVal computes the moments at pixel (x0, y0).",
            py::arg("x0"), py::arg("y0"), py::arg("radius"),
            py::arg("ret"))
        
        .def("getVarianceVal", ([](pic::Image* this_img, py::buffer mean_val_buffer,
                                   pic::BBox *box, py::buffer ret_buffer)
            {
                // Get the buffer information
                py::buffer_info info = ret_buffer.request();

                // Check if the buffer is type float
                if ( info.format != py::format_descriptor<float>::format() )
                    throw std::runtime_error("Incompatible buffer format," 
                                         "must be of float values.");
            
                // Get the raw pointer to the data
                float* ret = static_cast<float*>(info.ptr);

                // Get the buffer information
                py::buffer_info info_2 = mean_val_buffer.request();

                // Check if the buffer is type float
                if ( info_2.format != py::format_descriptor<float>::format() )
                    throw std::runtime_error("Incompatible buffer format," 
                                         "must be of float values.");
            
                // Get the raw pointer to the data
                float* mean_val = static_cast<float*>(info.ptr);

                // Call the function
                float* variance_val = this_img->getVarianceVal(mean_val, box, ret);

                // Create a NumPy array that owns the data of the float* array
                py::array_t<float, py::array::c_style> np_arr ({sizeof(variance_val) / sizeof(float)}, variance_val);

                // Return the NumPy array to Python
                return np_arr; 
            }),
            "getVarianceVal computes the variance for the current Image.",
            py::arg("meanVal"), py::arg("box"), py::arg("ret"))
            
        .def("getCovMtxVal", ([](pic::Image* this_img, py::buffer mean_val_buffer,
                                pic::BBox *box, py::buffer ret_buffer)
            {
                // Get the buffer information
                py::buffer_info info = ret_buffer.request();

                // Check if the buffer is type float
                if ( info.format != py::format_descriptor<float>::format() )
                    throw std::runtime_error("Incompatible buffer format," 
                                         "must be of float values.");
            
                // Get the raw pointer to the data
                float* ret = static_cast<float*>(info.ptr);

                // Get the buffer information
                py::buffer_info info_2 = mean_val_buffer.request();

                // Check if the buffer is type float
                if ( info_2.format != py::format_descriptor<float>::format() )
                    throw std::runtime_error("Incompatible buffer format," 
                                         "must be of float values.");
            
                // Get the raw pointer to the data
                float* mean_val = static_cast<float*>(info.ptr);

                // Call the function
                float* cov_mtx_val = this_img->getCovMtxVal(mean_val, box, ret);

                // Create a NumPy array that owns the data of the float* array
                py::array_t<float, py::array::c_style> np_arr ({sizeof(cov_mtx_val) / sizeof(float)}, cov_mtx_val);

                // Return the NumPy array to Python
                return np_arr; 
            }),
            "getVarianceVal computes the variance for the current Image.",
            py::arg("meanVal"), py::arg("box"), py::arg("ret"))
                
        .def("getPercentileVal", ([](pic::Image* this_img, float percentile,
                                  pic::BBox *box, py::buffer ret_buffer)
            {
                // Get the buffer information
                py::buffer_info info = ret_buffer.request();

                // Check if the buffer is type float
                if ( info.format != py::format_descriptor<float>::format() )
                    throw std::runtime_error("Incompatible buffer format," 
                                         "must be of float values.");
            
                // Get the raw pointer to the data
                float* ret = static_cast<float*>(info.ptr);

                // return the function
                return this_img->getPercentileVal(percentile, box, ret); 
            }),
            "getPercentileVal computes the median value value given a percentile.",
            py::arg("percentile"), py::arg("box"), py::arg("ret"))
        
        .def("getMedVal", ([](pic::Image* this_img, pic::BBox *box,
                           py::buffer ret_buffer)
            {
                // Get the buffer information
                py::buffer_info info = ret_buffer.request();

                // Check if the buffer is type float
                if ( info.format != py::format_descriptor<float>::format() )
                    throw std::runtime_error("Incompatible buffer format," 
                                         "must be of float values.");
            
                // Get the raw pointer to the data
                float* ret = static_cast<float*>(info.ptr);

                // Call the function
                float* med_val = this_img->getMedVal(box, ret);

                // Create a NumPy array that owns the data of the float* array
                py::array_t<float, py::array::c_style> np_arr ({sizeof(med_val) / sizeof(float)}, med_val);

                // Return the NumPy array to Python
                return np_arr;             }),
            "getMedVal",
            py::arg("box"), py::arg("ret"))
        
        .def("getDynamicRange", &pic::Image::getDynamicRange)
        
        .def("getdataUC", &pic::Image::getdataUC)
        
        .def("getColorSamples", ([](pic::Image* this_img, py::buffer samples_buffer,
                                   int &nSamples, float percentage)
            {
                // Get the buffer information
                py::buffer_info info = samples_buffer.request();

                // Check if the buffer is type float
                if ( info.format != py::format_descriptor<float>::format() )
                    throw std::runtime_error("Incompatible buffer format," 
                                            "must be of float values.");
            
                // Get the raw pointer to the data
                float* samples = static_cast<float*>(info.ptr);

                // Call the function
                float* color_samples = this_img->getColorSamples(samples,
                                                                nSamples, percentage);
                
                // Create a NumPy array that owns the data of the float* array
                py::array_t<float, py::array::c_style> np_arr ({sizeof(color_samples) / sizeof(float)},
                                                               color_samples);

                // Return the NumPy array to Python
                return np_arr; 

            }),
            "getColorSamples",
            py::arg("samples"), py::arg("nSamples"), py::arg("percentage"))
        
        .def("size", &pic::Image::size,
            "size computes the number of values.")
        
        .def("sizeFrame", &pic::Image::sizeFrame,
            "sizeFrame")
        
        .def("nPixels", &pic::Image::nPixels,
            "nPixels")
        
        .def("checkCoordinates", &pic::Image::checkCoordinates,
            "checkCoordinates checks (x, y, z) coordinates)" 
            "if they are valid or not.",
            py::arg("x"), py::arg("y"), py::arg("z")=0)
        
        .def("convertFromMask", &pic::Image::convertFromMask,
            "convertFromMask converts a boolean mask into an Image." 
            "true is mapped to 1.0f, and false is mapped to 0.0f.",
            py::arg("mask"), py::arg("width"), py::arg("height"))
        
        /*.def("convertToMask", ([](py::buffer color_buffer, float threshold, 
                               bool cmp, py::buffer mask)
            {
                
            }),
            "convertToMask converts an Image into a boolean mask.",
            py::arg("color"), py::arg("threshold"), py::arg("cmp"),
            py::arg("mask"))
        */
/*       
        .def("getFlippedEXR", &pic::Image::getFlippedEXR)
        
        .def("removeSpecials", &pic::Image::removeSpecials)
        
        .def("clamp", &pic::Image::clamp)
        
        .def("calculateStrides", &pic::Image::calculateStrides)
        
        .def("getLL", &pic::Image::getLL)
        
        .def("getNormalizedCoords", &pic::Image::getNormalizedCoords)

//⚠⚠⚠ check the two getAddress for static_cast ⚠⚠⚠ 

        .def("getAddres",static_cast <int (pic::Image::*)(int, int)>(&pic::Image::getAddress))
        .def("getAddres",static_cast <int (pic::Image::*)(int, int, int)>(&pic::Image::getAddress))
        .def("reverseAddress", &pic::Image::reverseAddress)

//⚠⚠⚠ check why allocateSimilar One won't bind, probably needs a smart_pointer
//      .def("allocateSimilarOne"), &pic::Image:allocateSimilarOne

        .def("allocateSimilarTo", &pic::Image::allocateSimilarTo)
        .def("clone", &pic::Image::clone)
        .def("Read", &pic::Image::Read)
        .def("Write", &pic::Image::Write,
                py::arg("nameFile"), py::arg("typeWrite")=pic::LT_NOR_GAMMA,
                py::arg("writeCounter")=0)
        .def("changeOwnership", &pic::Image::changeOwnership)

        .def("getDiagonalSize", &pic::Image::getDiagonalSize)
*/        

    //endregion
 /*   
    // region Operators
        //.def("__setattr__", [](pic::Image& self, const pic::Image& a) -> void {
        //    return self.assign(&a);
        //}, py::arg("self"), py::arg("a"))
        //missing operato =(const float &a)
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
*/

    //region Args
    //⚠⚠⚠ For now all the variables are readonly, change them as the project goes on. ⚠⚠⚠

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


