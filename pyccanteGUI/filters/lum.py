import pyccante as pyc
from PySide6.QtWidgets import (QLabel, QPushButton, QHBoxLayout,
                               QVBoxLayout, QDialog, QComboBox)


class LumWindow(QDialog):
    def __init__(self, img):
        super(LumWindow, self).__init__()
        self.img = img
        self.setWindowTitle("Luminance...")

        # Define labels for parameters
        self.type_label = QLabel("Type: ")

        # Define line edits for parameters
        self.type_menu = QComboBox()
        self.type_menu.addItem("CIE_Luminance")
        self.type_menu.addItem("Luma")
        self.type_menu.addItem("Ward_Luminance")
        self.type_menu.addItem("Mean")

        # Put labels and line edits into a layout
        self.type_layout = QHBoxLayout()
        self.type_layout.addWidget(self.type_label)
        self.type_layout.addWidget(self.type_menu)

        # Define buttons
        self.OK_button = QPushButton("OK")
        self.Cancel_button = QPushButton("Cancel")
        self.OK_button.clicked.connect(self.execute)
        self.Cancel_button.clicked.connect(self.hide)

        # Put buttons into a layout
        self.buttons_layout = QHBoxLayout()
        self.buttons_layout.addWidget(self.OK_button)
        self.buttons_layout.addWidget(self.Cancel_button)

        # Construct windows
        self.main_layout = QVBoxLayout(self)
        self.main_layout.addLayout(self.type_layout)
        self.main_layout.addLayout(self.buttons_layout)

    def execute(self):
        type_lum = self.ret_luminance()
        new_img = pyc.FilterLuminance.execute(self.img, type_lum)
        if new_img is not None:
            self.img = new_img
        self.hide()

    def ret_luminance(self):
        # Returns the Luminance specified in the drowdown menu
        if self.type_menu.currentText() == "CIE_Luminance":
            return pyc.LUMINANCE_TYPE.LT_CIE_LUMINANCE
        elif self.type_menu.currentText() == "Luma":
            return pyc.LUMINANCE_TYPE.LT_LUMA
        elif self.type_menu.currentText() == "Ward_Luminance":
            return pyc.LUMINANCE_TYPE.LT_WARD_LUMINANCE
        elif self.type_menu.currentText() == "Mean":
            return pyc.LUMINANCE_TYPE.LT_MEAN
