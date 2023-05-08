#ifndef PYCCANTE_PY_IMAGE_CPP
#define PYCCANTE_PY_IMAGE_CPP

#include <GL/glew.h>
#include <piccante.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>

namespace py = pybind11;
using namespace py::literals;



void init_Image(pybind11::module_& m)
{

// region LDR_type
// ⚠⚠⚠ Remember to move this binding in py_dynamic_range.cpp ⚠⚠⚠

    py::enum_<pic::LDR_type>(m, "LDR_type")
        .value("LT_NOR", pic::LDR_type::LT_NOR)
        .value("LT_NOR_GAMMA", pic::LDR_type::LT_NOR_GAMMA)
        .value("LT_LDR", pic::LDR_type::LT_LDR)
        .value("LT_NONE", pic::LDR_type::LT_NONE);

// endregion

// region Image

    // region Constructors

    py::class_<pic::Image>(m, "Image")
        .def(py::init<> ())

        .def(py::init( [](pic::Image *imgIn, bool deepCopy){
            return new pic::Image(imgIn, deepCopy);
        }), py::arg("imgIn"), py::arg("channels")) 
        
        .def(py::init<std::string &, pic::LDR_type>())

        .def(py::init<int /*width*/, int/*height*/, int/*channels*/>()) 

        .def(py::init( [](py::buffer color_buffer, int channels) {
            // Get the buffer information
            py::buffer_info info = color_buffer.request();

            if (info.format != py::format_descriptor<float>::format())
                throw std::runtime_error("Incompatible buffer format, must be of float values.");
            
            // Get the raw pointer to the data
            float* color = static_cast<float*>(info.ptr);

            //⚠⚠⚠ Chiedere se va bene come condizione ⚠⚠⚠
            if(! info.ndim == channels )
                throw std::runtime_error("the number of channels must be the same as the dimension of color.");
            // Return a new instance of Image
            return new pic::Image(color, channels);
            }), py::arg("color"), py::arg("channels"))

        .def(py::init( []( int frames, int width, int height,
            int channels, py::buffer data_buffer) {
            // Get the buffer information
            py::buffer_info info = data_buffer.request();

            if(info.format != py::format_descriptor<float>::format())
                throw std::runtime_error("Incompatible buffer format, must be of float values.");            

            // Get the raw pointer to the data
            float* data = static_cast<float*>(info.ptr);

            //⚠⚠⚠ Chiedere se va bene come condizione ⚠⚠⚠
            if(! info.size == (frames * width * height * channels))            
                throw std::runtime_error("the buffer is not the correct size");
            
            //Return a new instance of Image
            return new pic::Image(frames, width, height, channels, data);
            }), py::arg("frames"), py::arg("width"), py::arg("height"),
                py::arg("channels"), py::arg("data"))

    // endregion
    
    // region Destructors

    //⚠⚠⚠ Implementare il destructor ~Image() ⚠⚠⚠
        
    // endregion

    //region Functions

        .def("allocate", &pic::Image::allocate)
        .def("allocateAux", &pic::Image::allocateAux)
        .def("release", &pic::Image::release)
        .def("copySubImage", &pic::Image::copySubImage)
        .def("scaleCosine", &pic::Image::scaleCosine)
        .def("flipH", &pic::Image::flipH)
        .def("flipV", &pic::Image::flipV)
        .def("flipHV", &pic::Image::flipHV)
        .def("rotate90CCW", &pic::Image::rotate90CCW)
        .def("rotate90CW", &pic::Image::rotate90CW)
        .def("getDiagonalSize", &pic::Image::getDiagonalSize)
        .def("setZero", &pic::Image::setZero)
        .def("setRand", &pic::Image::setRand)
        .def("isValid", &pic::Image::isValid)
        .def("isSimilarType", &pic::Image::isSimilarType)
        .def("assign", &pic::Image::assign)
        .def("blend", &pic::Image::blend)
        .def("minimum", &pic::Image::minimum)
        .def("maximum", &pic::Image::maximum)
        .def("applyFunction", &pic::Image::applyFunction)
        .def("applyFunctionParam", &pic::Image::applyFunctionParam)

//⚠⚠⚠ Tutte le funzioni commentate fanno uso o ritornano un
//    oggetto di tipo BBox che per ora non è stato bindizzato
//      .def("getFullBox", &pic::Image::getFullBox)
//      .def("getMaxVal", &pic::Image::getMaxVal)
//      .def("getMinVal", &pic::Image::getMinVal)
//      .def("getLogMeanVal", &pic::Image::getLogMeanVal)
//      .def("getSumVal", &pic::Image::getSumVal)
//      .def("getMeanVal", &pic::Image::getMeanVal)
//      .def("getMomentsVal", &pic::Image::getMomentsVal)
//      .def("getVarianceVal", &pic::Image::getVarianceVal)
//      .def("getCovMtxVal", &pic::Image::getCovMtxVal)
//      .def("getPercentileVal", &pic::Image::getPercentileVal)
//      .def("getMedVal", &pic::Image::getMedVal)

        .def("getDynamicRange", &pic::Image::getDynamicRange)
        .def("getdataUC", &pic::Image::getdataUC)
        .def("getColorSamples", &pic::Image::getColorSamples)
        .def("size", &pic::Image::size)
        .def("sizeFrame", &pic::Image::sizeFrame)
        .def("nPixels", &pic::Image::nPixels)
        .def("checkCoordinates", &pic::Image::checkCoordinates)
        .def("convertFromMask", &pic::Image::convertFromMask)
        .def("convertToMask", &pic::Image::convertToMask)
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
        

    //endregion
    
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

// endregion

}


#endif /* PYCCANTE_PY_IMAGE_CPP */