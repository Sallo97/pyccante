# tesi_pyccante
Progetto di tesi triennale unipi, basato sulla libreria di elaborazione delle immagini High Dynamic Range (HDR) Piccante.
Il progetto consiste nella realizzazione di un binding in Python 3.x per la libreria, facendo uso dei framework NumPy e/o PyTorch
per poterla utilizzare in futuro per deep-learning.

# corso HDR

http://www.banterle.com/francesco/courses/2015/hdri/

# opencv binding

https://github.com/opencv/opencv-python

https://github.com/cnr-isti-vclab/PyMeshLab

https://github.com/wjakob/nanobind

https://github.com/pybind/pybind11

# core [DONE]

histogram [DONE]

image [DONE]


# filtri [DONE]

filter_luminance.hpp  [DONE]

filter_bilateral_2df.hpp  [DONE]

filter_bilateral_2ds.hpp  [DONE]

filter_gaussian_2d.hpp  [DONE]

filter_conv_2d.hpp  [DONE]

filter_max.hpp  [DONE]

filter_mean.hpp [DONE]

filter_med.hpp  [DONE]

filter_med_vec.hpp [DONE]

filter_mosaic.hpp [DONE]

filter_warp_2d.hpp  [DONE]

filter_rotation.hpp [DONE]

# algorithms

hdr_merger.hpp [DONE]

grow_cut.hpp  [DONE]

poisson_solver.hpp  [DONE]

connected_components.hpp [???]

camera_response_function.hpp 

# tone_mapping  [DONE]

ward_histogram_tmo.hpp [DONE]

reinhard_tmo.hpp [DONE]

exposure_fusion.hpp [DONE]

durand_tmo.hpp [DONE]

drago_tmo.hpp [DONE]
