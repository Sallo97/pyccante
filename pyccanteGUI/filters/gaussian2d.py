import pyccante as pyc
from layouts import warningwin as ww
from PySide6.QtWidgets import (QLabel, QPushButton, QLineEdit,
                               QHBoxLayout, QVBoxLayout, QDialog)


class Gauss2DWindow(QDialog):
    def __init__(self, img):
        super(Gauss2DWindow, self).__init__()
        self.img = img
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
        self.Cancel_button.clicked.connect(self.hide)

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
            self.img = new_img
            self.hide()
        else:
            warning_window = ww.WarningWindow("Sigma must be greater than 0!")
            warning_window.exec_()