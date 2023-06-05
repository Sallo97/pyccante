import pyccante as pyc
from layouts.windows import warningwin as ww
from PySide6.QtWidgets import (QLabel, QPushButton, QHBoxLayout, QVBoxLayout, QDialog,
                               QListWidget, QFileDialog, QGridLayout)
from PySide6.QtCore import Qt
from utils import path
from itertools import islice


class HDRMergeWindow(QDialog):
    def __init__(self):
        super(HDRMergeWindow, self).__init__()
        self.img = None
        self.path = path.get_hdr_path()
        self.img_dict = {}
        self.setWindowTitle("HDR Merge...")

        # Define images list
        self.img_list = QListWidget()
        img_list_name = QLabel("Images")
        img_list_name.setAlignment(Qt.AlignCenter)

        self.exp_list = QListWidget()
        self.exp_list.setFixedWidth(100)
        exp_list_name = QLabel("Exposure Time")
        exp_list_name.setAlignment(Qt.AlignCenter)

        # Define layout for list
        full_list = QGridLayout()
        full_list.addWidget(img_list_name, 0, 0)
        full_list.addWidget(exp_list_name, 0, 1)
        full_list.addWidget(self.img_list, 1, 0)
        full_list.addWidget(self.exp_list, 1, 1)

        # Define add button
        self.add_button = QPushButton("Add Image")
        self.add_button.clicked.connect(self.add_image)
        self.rmv_button = QPushButton("Remove Image")
        self.rmv_button.clicked.connect(self.rmv_from_win)

        # Define buttons
        self.OK_button = QPushButton("OK")
        self.Cancel_button = QPushButton("Cancel")
        self.OK_button.clicked.connect(self.execute)
        self.Cancel_button.clicked.connect(self.hide_window)

        # Put buttons into a layout
        self.buttons_layout = QHBoxLayout()
        self.buttons_layout.addWidget(self.OK_button)
        self.buttons_layout.addWidget(self.Cancel_button)

        # Construct windows
        self.main_layout = QVBoxLayout(self)
        self.main_layout.addLayout(full_list)
        self.main_layout.addWidget(self.add_button)
        self.main_layout.addWidget(self.rmv_button)
        self.main_layout.addLayout(self.buttons_layout)

    def rmv_from_win(self):
        if self.img_list.currentItem() is not None:
            idx = self.img_list.currentRow()
            del self.img_dict[next(islice(self.img_dict, idx, None))]
            self.img_list.takeItem(idx)
            self.exp_list.takeItem(idx)

    def rmv_from_list(self):
        if self.img_list.currentItem() is not None:
            for i in self.img_dict.keys():
                name = i.split("/")[-1]
                print(f"name = {name}")
                if name == self.img_list.currentItem().text().split("(")[0]:
                    print(f"removing {i}")
                    self.img_dict.pop(i)
                    break

    def execute(self):
        if len(self.img_dict.keys()) > 0:
            if len(self.img_dict.keys()) <= 2:
                war_win = ww.WarningWindow("Warning: although the algorithm works,\n"
                                           "it is raccomended to use at least 3 images.")
                war_win.exec()
            exec_obj = pyc.HDRMerger()
            for img in self.img_dict.keys():
                exec_obj.addFile(img, self.img_dict[img])
            new_img = exec_obj.execute()
            if new_img is not None:
                self.img = new_img
                self.hide_window()
        else:
            war_win = ww.WarningWindow("You didn't select any image for HDR merge!\n"
                                       "The filter was not applied.")
            war_win.exec()

    def get_exposure(self, name_file):
        ext = name_file.split(".")[-1]
        if ext == "jpg":
            exposure = pyc.getJPGExposure(name_file)
            return exposure
        else:
            return -1.0

    def add_image(self):
        new_path = QFileDialog.getOpenFileName(
            self,
            "Open Conv",
            "./data",
            "Image Files (*.png *.jpg *.hdr)")
        if new_path[0] != "":
            exposure = self.get_exposure(new_path[0])
            self.img_dict[new_path[0]] = exposure
            name_file = new_path[0].split("/")
            self.img_list.addItem(f"{name_file[-1]}")
            self.exp_list.addItem(f"{exposure}")
            idx = self.img_list.count()
            item = self.exp_list.item(idx-1)
            item.setFlags(item.flags() | Qt.ItemIsEditable)

    def hide_window(self):
        self.img_list.clear()
        self.hide()
