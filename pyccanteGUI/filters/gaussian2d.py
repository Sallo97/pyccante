import pyccante as pyc
import imgwindow as iw
from PySide6.QtWidgets import (QLabel, QPushButton, QLineEdit,
                               QHBoxLayout, QVBoxLayout, QDialog)


class Gauss2DWindow(QDialog):
    def __init__(self, img, path, win, ldr_type):
        self.img = img
        self.path = path
        self.win = win
        self.ldr_type = ldr_type
        self.modified = False
        super(Gauss2DWindow, self).__init__()
        self.setWindowTitle("Conv2D...")

        # Define labels for parameters
        self.sigma_label = QLabel("Sigma: ")

        # Define line edits for parameters
        self.sigma_edit = QLineEdit("0")

        # Put labels and line edits into a layout
        self.sigma_layout = QHBoxLayout()
        self.sigma_layout.addWidget(self.sigma_label)
        self.sigma_layout.addWidget(self.sigma_edit)

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
        self.main_layout.addLayout(self.sigma_layout)
        self.main_layout.addLayout(self.buttons_layout)

    def execute(self):
        sigma = float(self.sigma_edit.text())
        if sigma > 0:
            new_img = pyc.FilterGaussian2D.execute(self.img, sigma=sigma)
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
