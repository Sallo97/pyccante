import pyccante as pyc
import imgwindow as iw
from PySide6.QtWidgets import (QLabel, QPushButton, QHBoxLayout,
                               QVBoxLayout, QDialog)


class MosaicWindow(QDialog):
    def __init__(self, img, path, win, ldr_type):
        self.img = img
        self.path = path
        self.win = win
        self.ldr_type = ldr_type
        self.modified = False
        super(MosaicWindow, self).__init__()
        self.setWindowTitle("Mosaic...")

        # Define labels for parameters
        self.ask_label = QLabel("Apply the Filter?")

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
        self.main_layout.addWidget(self.ask_label)
        self.main_layout.addLayout(self.buttons_layout)

    def execute(self):
        new_img = pyc.FilterMosaic.execute(self.img)
        if new_img is not None:
            self.img = new_img
            self.img.Write(self.path, self.ldr_type)
            # iw.update_pixmap(self.win, self.path)
            self.modified = True
        self.hide_window()

    def hide_window(self):
        self.hide()

    def update_infos(self, img, path, win, ldr_type):
        self.img = img
        self.path = path
        self.win = win
        self.ldr_type = ldr_type
