# this file contains the class Slider

from PySide6.QtWidgets import QSlider
from PySide6.QtCore import Qt


class Slider(QSlider):
    def __init__(self, r_min, r_max):
        # Creates a horizontal slider
        # min = the minimum range
        # max = the maximum range
        super(Slider, self).__init__()
        self.setOrientation(Qt.Orientation.Horizontal)
        self.setRange(r_min, r_max)
        self.setFixedHeight(10)
        self.setFixedWidth(150)
