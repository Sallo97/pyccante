import pyccante as pyc
import imgwindow as iw
from PySide6.QtWidgets import (QLabel, QPushButton, QHBoxLayout,
                               QVBoxLayout, QDialog, QComboBox)


class LumWindow(QDialog):
    def __init__(self, img, path, win, ldr_type):
        self.img = img
        self.path = path
        self.win = win
        self.ldr_type = ldr_type
        self.modified = False
        super(LumWindow, self).__init__()
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
        self.Cancel_button.clicked.connect(self.hide_window)

        # Put buttons into a layout
        self.buttons_layout = QHBoxLayout()
        self.buttons_layout.addWidget(self.OK_button)
        self.buttons_layout.addWidget(self.Cancel_button)

        # Construct window
        self.main_layout = QVBoxLayout(self)
        self.main_layout.addLayout(self.type_layout)
        self.main_layout.addLayout(self.buttons_layout)

    def execute(self):
        type_lum = self.ret_luminance()
        new_img = pyc.FilterLuminance.execute(self.img, type_lum)
        if new_img is not None:
            self.img = new_img
            self.img.Write(self.path, self.ldr_type)
            # iw.update_pixmap(self.win, self.path)
            self.modified = True
        self.hide_window()

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

    def hide_window(self):
        self.hide()

    def update_infos(self, img, path, win, ldr_type):
        self.img = img
        self.path = path
        self.win = win
        self.ldr_type = ldr_type
