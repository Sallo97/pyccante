from layouts.windows import warningwin as ww
from bars import file as fl
import utils.str_warning as sw
from layouts.windows import warningwin as ww
from PySide6.QtWidgets import (QLabel, QPushButton,
                               QHBoxLayout, QVBoxLayout,
                               QFileDialog, QDialog)


class Blend(QDialog):
    def __init__(self, img):
        super(Blend, self).__init__()
        self.img = img
        self.blend = None
        self.weight = None

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
        self.Cancel_button.clicked.connect(self.hide)

        # Put buttons into a layout
        self.buttons_layout = QHBoxLayout()
        self.buttons_layout.addWidget(self.OK_button)
        self.buttons_layout.addWidget(self.Cancel_button)

        # Construct windows
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
            self.hide()

    def check_none(self):
        if self.blend is not None or self.weight is not None:
            return True
        else:
            ww.WarningWindow(sw.missing_images_str()).exec()
            return False

    def check_sizes(self):
        if self.blend.size() == self.img.size() and self.weight.size() == self.img.size():
            return True
        else:
            ww.WarningWindow(sw.invalid_size_str()).exec()
            return False

    def open_blend(self):
        new_path = QFileDialog.getOpenFileName(
            self,
            "Open blend image",
            "./data",
            "Image Files (*.png *.jpg *.hdr)")
        self.blend = fl.read_img(new_path[0])
        name_file = new_path[0].split("/")
        self.blend_button.setText(f"{name_file[-1]}")

    def open_weight(self):
        new_path = QFileDialog.getOpenFileName(
            self,
            "Open weight image",
            "./data",
            "Image Files (*.png *.jpg *.hdr)")
        self.weight = fl.read_img(new_path[0])
        name_file = new_path[0].split("/")
        self.weight_button.setText(f"{name_file[-1]}")
