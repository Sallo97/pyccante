import pyccante as pyc
import imgwindow as iw
import numpy as np
import warningwin as ww
from PySide6.QtWidgets import (QLabel, QPushButton, QHBoxLayout,
                               QLineEdit, QVBoxLayout, QDialog,
                               QCheckBox, QGridLayout)


class Warp2DWindow(QDialog):
    def __init__(self, img, path, win, ldr_type):
        self.img = img
        self.path = path
        self.win = win
        self.ldr_type = ldr_type
        self.modified = False
        super(Warp2DWindow, self).__init__()
        self.setWindowTitle("Warp2D...")
        self.war_win = ww.WarningWindow("The determinant is negative!"
                                        "\nTry again with another matrix.")

        # Define labels for parameters
        self.mtx_label = QLabel("Matrix: ")

        # Define line edits for parameters
        self.r1c1_edit = QLineEdit("0")
        self.r1c2_edit = QLineEdit("0")
        self.r1c3_edit = QLineEdit("0")

        self.r2c1_edit = QLineEdit("0")
        self.r2c2_edit = QLineEdit("0")
        self.r2c3_edit = QLineEdit("0")

        self.r3c1_edit = QLineEdit("0")
        self.r3c2_edit = QLineEdit("0")
        self.r3c3_edit = QLineEdit("0")



        # Put row and mtx edit together
        self.rc_layout = QGridLayout()

        # Define first row of matrix
        self.rc_layout.addWidget(self.r1c1_edit, 0, 0)
        self.rc_layout.addWidget(self.r1c2_edit, 0, 1)
        self.rc_layout.addWidget(self.r1c3_edit, 0, 2)

        # Define second row of matrix
        self.rc_layout.addWidget(self.r2c1_edit, 1, 0)
        self.rc_layout.addWidget(self.r2c2_edit, 1, 1)
        self.rc_layout.addWidget(self.r2c3_edit, 1, 2)

        # Define third row of matrix
        self.rc_layout.addWidget(self.r3c1_edit, 2, 0)
        self.rc_layout.addWidget(self.r3c2_edit, 2, 1)
        self.rc_layout.addWidget(self.r3c3_edit, 2, 2)

        # Define mtx
        self.mtx_layout = QHBoxLayout()
        self.mtx_layout.addWidget(self.mtx_label)
        self.mtx_layout.addLayout(self.rc_layout, stretch=1)

        # Define checkboxes
        self.size = QCheckBox("Same size")
        self.cntr = QCheckBox("Centroid")
        self.checks = QHBoxLayout()
        self.checks.addWidget(self.size)
        self.checks.addWidget(self.cntr)

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
        self.main_layout.addLayout(self.mtx_layout)
        self.main_layout.addLayout(self.checks)
        self.main_layout.addLayout(self.buttons_layout)

    def execute(self):
        same_size = self.size.isChecked()
        centroid = self.cntr.isChecked()
        print(f"centroid = {centroid}")
        print(f"same_size = {same_size}")
        print(f"img = {self.img.nameFile}")
        mtx = self.create_mtx()
        if mtx.determinant() > 0:
            new_img = pyc.Image()
            new_img = pyc.FilterWarp2D.execute(self.img, imgOut=new_img, h=mtx,
                                               bSameSize=same_size, bCentroid=centroid)
            print(f"new_img = {new_img.nameFile}")
            if new_img is not None:
                self.img = new_img
                self.img.Write(self.path, self.ldr_type)
                # iw.update_pixmap(self.win, self.path)
                self.modified = True
                self.hide_window()
        else:
            self.war_win.exec()

    def create_mtx(self):
        mtx = np.array([ float(self.r1c1_edit.text()), float(self.r1c2_edit.text()), float(self.r1c3_edit.text()),
                         float(self.r2c1_edit.text()), float(self.r2c2_edit.text()), float(self.r2c3_edit.text()),
                         float(self.r3c1_edit.text()), float(self.r3c2_edit.text()), float(self.r3c3_edit.text())],
                       np.float32)

        mtx3x3 = pyc.Matrix3x3(mtx)
        print(mtx3x3)
        return mtx3x3

    def hide_window(self):
        self.hide()

    def update_infos(self, img, path, win, ldr_type):
        self.img = img
        self.path = path
        self.win = win
        self.ldr_type = ldr_type
