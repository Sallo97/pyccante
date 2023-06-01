import pyccante as pyc
import imgwindow as iw
from PySide6.QtWidgets import (QLabel, QPushButton, QLineEdit,
                               QHBoxLayout, QVBoxLayout, QDialog)


class RotationWindow(QDialog):
    def __init__(self, img, path, win, ldr_type):
        self.img = img
        self.path = path
        self.win = win
        self.ldr_type = ldr_type
        self.modified = False
        super(RotationWindow, self).__init__()
        self.setWindowTitle("Bilateral2DF...")

        # Define labels for parameters
        self.angle_x_label = QLabel("Angle X: ")
        self.angle_y_label = QLabel("Angle Y: ")
        self.angle_z_label = QLabel("Angle Z: ")

        # Define line edits for parameters
        self.angle_x_edit = QLineEdit("0")
        self.angle_y_edit = QLineEdit("0")
        self.angle_z_edit = QLineEdit("0")

        # Put labels and line edits into a layout
        self.angle_x_layout = QHBoxLayout()
        self.angle_x_layout.addWidget(self.angle_x_label)
        self.angle_x_layout.addWidget(self.angle_x_edit)

        self.angle_y_layout = QHBoxLayout()
        self.angle_y_layout.addWidget(self.angle_y_label)
        self.angle_y_layout.addWidget(self.angle_y_edit)

        self.angle_z_layout = QHBoxLayout()
        self.angle_z_layout.addWidget(self.angle_z_label)
        self.angle_z_layout.addWidget(self.angle_z_edit)

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
        self.main_layout.addLayout(self.angle_x_layout)
        self.main_layout.addLayout(self.angle_y_layout)
        self.main_layout.addLayout(self.angle_z_layout)
        self.main_layout.addLayout(self.buttons_layout)

    def execute(self):
        angle_x = float(self.angle_x_edit.text())
        angle_y = float(self.angle_y_edit.text())
        angle_z = float(self.angle_z_edit.text())
        new_img = pyc.FilterRotation.execute(self.img, angle_x,
                                             angle_y, angle_z)
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
