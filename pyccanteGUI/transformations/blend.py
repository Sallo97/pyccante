import pyccante as pyc
import imgwindow as iw
import warningwin as ww
from menubar import file as fl
from PySide6.QtWidgets import (QLabel, QPushButton,
                               QHBoxLayout, QVBoxLayout,
                               QFileDialog, QDialog)


class Blend(QDialog):
    def __init__(self, img, path, win, ldr_type):
        super(Blend, self).__init__()
        self.img = img
        self.blend = None
        self.weight = None
        self.path = path
        self.win = win
        self.ldr_type = ldr_type

        self.setWindowTitle("Blend...")

        # Define labels for parameters
        self.blend_label = QLabel("to blend: ")
        self.weight_label = QLabel("weight: ")

        # Define button for imgEdge
        self.blend_button = QPushButton("Open...")
        self.blend_button.clicked.connect(self.open_blend)

        self.weight_button = QPushButton("Open...")
        self.weight_button.clicked.connect(self.open_weight)

        # Put labels and buttons into a layout
        self.blend_layout = QHBoxLayout()
        self.blend_layout.addWidget(self.blend_label)
        self.blend_layout.addWidget(self.blend_button)

        self.weight_layout = QHBoxLayout()
        self.weight_layout.addWidget(self.weight_label)
        self.weight_layout.addWidget(self.weight_button)

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
        self.main_layout.addLayout(self.blend_layout)
        self.main_layout.addLayout(self.weight_layout)
        self.main_layout.addLayout(self.buttons_layout)

    def execute(self):
        print(f"Executing blend with:\n"
              f"img = {self.img.nameFile}\n"
              f"blend = {self.blend.nameFile}\n"
              f"weight = {self.weight.nameFile}")
        if self.check_none() and self.check_sizes():
            self.img.blend(self.blend, self.weight)
            print("Blend executed!")

            self.img.Write(self.path, self.ldr_type)
            print(f"Image written in {self.path}")
            iw.update_pixmap(self.win, self.path)
            self.hide_window()


    def check_none(self):
        if self.blend is not None or self.weight is not None:
            return True
        else:
            war_win = ww.WarningWindow("You didn't select a 'to blend' and 'weight' image!"
                                       "\nThe filter was not applied.")
            war_win.exec()
            return False

    def check_sizes(self):
        if self.blend.size() == self.img.size() and self.weight.size() == self.img.size():
            return True
        else:
            war_win = ww.WarningWindow("The 'to blend', 'weight' and 'image' must have the same size!"
                                       "\nThe filter was not applied.")
            war_win.exec()
            return False
    def hide_window(self):
        self.blend_button.setText("Open...")
        self.weight_button.setText("Open...")
        self.blend = None
        self.weight = None
        self.hide()

    def update_infos(self, img, path, win, ldr_type):
        self.img = img
        self.path = path
        self.win = win
        self.ldr_type = ldr_type
        print(f"updated with path = {self.path}")

    def open_blend(self):
        path = QFileDialog.getOpenFileName(
            self,
            "Open blend image",
            "./data",
            "Image Files (*.png *.jpg *.hdr)")
        self.blend = fl.read_img(path[0], None, None)
        name_file = path[0].split("/")
        self.blend_button.setText(f"{name_file[-1]}")

    def open_weight(self):
        path = QFileDialog.getOpenFileName(
            self,
            "Open weight image",
            "./data",
            "Image Files (*.png *.jpg *.hdr)")
        self.weight = fl.read_img(path[0], None, None)
        name_file = path[0].split("/")
        self.weight_button.setText(f"{name_file[-1]}")