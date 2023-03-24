# tesi_pyccante
Progetto di tesi triennale unipi, basato sulla libreria di elaborazione delle immagini High Dynamic Range (HDR) Piccante.
Il progetto consiste nella realizzazione di un binding in Python 3.x per la libreria, facendo uso dei framework NumPy e/o PyTorch
per poterla utilizzare in futuro per deep-learning.

#corso HDR
http://www.banterle.com/francesco/courses/2015/hdri/

#filtri
filter_luminance.hpp
filter_bilateral_2df.hpp
filter_bilateral_2ds.hpp
filter_gaussian_2d.hpp
filter_conv_2d.hpp
filter_max.hpp
filter_mean.hpp 
filter_med.hpp
filter_med_vec.hpp
filter_mosaic.hpp
filter_assemble_hdr.hpp
filter_rotation.hpp

#algorithms
hdr_merger.hpp 
grow_cut.hpp
poisson_solver.hpp
connected_components.hpp 
camera_response_function.hpp 

#tone_mapping
ward_histogram_tmo.hpp 
reinhard_tmo.hpp 
exposure_fusion.hpp 
durand_tmo.hpp 
drago_tmo.hpp 
