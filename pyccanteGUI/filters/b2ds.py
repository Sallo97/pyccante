import pyccante as pyc
import imgwindow as iw
from menubar import file as fl
from PySide6.QtWidgets import (QLabel, QPushButton, QLineEdit,
                               QHBoxLayout, QVBoxLayout, QFileDialog, QDialog)


class B2DSWindow(QDialog):
    def __init__(self, img, path, win, ldr_type):
        self.img = img
        self.imgedge = None
        self.path = path
        self.win = win
        self.ldr_type = ldr_type
        self.modified = False
        super(B2DSWindow, self).__init__()
        self.setWindowTitle("Bilateral2DS...")

        # Define labels for parameters
        self.imgEdge_label = QLabel("Image Edge: ")
        self.sigma_s_label = QLabel("Sigma_s: ")
        self.sigma_r_label = QLabel("Sigma_r: ")

        # Define button for imgEdge
        self.imgEdge_button = QPushButton("Open...")
        self.imgEdge_button.clicked.connect(self.open_imgedge)

        # Define line edits for parameters
        self.sigma_s_line_edit = QLineEdit("0")
        self.sigma_r_line_edit = QLineEdit("0")

        # Put labels and line edits into a layout
        self.imgEdge_label_layout = QHBoxLayout()
        self.imgEdge_label_layout.addWidget(self.imgEdge_label)
        self.imgEdge_label_layout.addWidget(self.imgEdge_button)

        self.sigma_s_layout = QHBoxLayout()
        self.sigma_s_layout.addWidget(self.sigma_s_label)
        self.sigma_s_layout.addWidget(self.sigma_s_line_edit)

        self.sigma_r_layout = QHBoxLayout()
        self.sigma_r_layout.addWidget(self.sigma_r_label)
        self.sigma_r_layout.addWidget(self.sigma_r_line_edit)

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
        self.main_layout.addLayout(self.imgEdge_label_layout)
        self.main_layout.addLayout(self.sigma_s_layout)
        self.main_layout.addLayout(self.sigma_r_layout)
        self.main_layout.addLayout(self.buttons_layout)

    def execute(self):
        print(f"Entering with {self.img}")
        sigma_s = float(self.sigma_s_line_edit.text())
        sigma_r = float(self.sigma_r_line_edit.text())
        if self.imgedge is not None:
            new_img = pyc.FilterBilateral2DS.execute(self.img, imgEdge=self.imgedge,
                                                     sigma_s=sigma_s, sigma_r=sigma_r)
        else:
            new_img = pyc.FilterBilateral2DS.execute(self.img, sigma_s=sigma_s,
                                                     sigma_r=sigma_r)
        print(f"Finished with {new_img}")
        if new_img is not None:
            self.img = new_img
            self.img.Write(self.path, self.ldr_type)
            # iw.update_pixmap(self.win, self.path)
            self.modified = True
        self.hide_window()

    def hide_window(self):
        self.imgEdge_button.setText("Open...")
        self.hide()

    def update_infos(self, img, path, win, ldr_type):
        self.img = img
        self.path = path
        self.win = win
        self.ldr_type = ldr_type

    def open_imgedge(self):
        path = QFileDialog.getOpenFileName(
            self,
            "Open Image Edge",
            "./data",
            "Image Files (*.png *.jpg *.hdr)")
        self.imgedge = fl.read_img(path[0], None, None)
        name_file = path[0].split("/")
        self.imgEdge_button.setText(f"{name_file[-1]}")
