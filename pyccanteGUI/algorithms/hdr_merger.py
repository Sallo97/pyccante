import pyccante as pyc
import imgwindow as iw
import warningwin as ww
from PySide6.QtWidgets import (QLabel, QPushButton, QLineEdit,
                               QHBoxLayout, QVBoxLayout, QDialog,
                               QListWidget, QFileDialog, QGridLayout)
from PySide6.QtCore import Qt
from PySide6.QtGui import QWheelEvent
from itertools import islice


class HDRMergeWindow(QDialog):
    def __init__(self, img, path, win, ldr_type):
        self.img = img
        self.path = path
        self.win = win
        self.ldr_type = ldr_type
        self.modified = False
        self.img_dict = {}
        super(HDRMergeWindow, self).__init__()
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

        # Construct window
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
        print(self.img_dict)
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
                self.modified = True
                self.img = new_img
                tmo_img = pyc.ReinhardTMO.executeGlobal1(self.img)
                tmo_img.Write("./data/_hdr_temp.png", pyc.LDR_type.LT_NOR)
                self.win.update_pixmap(new_img.width, new_img.height, self.path)
                self.hide_window()
        else:
            war_win = ww.WarningWindow("You didn't select any image for HDR merge!\n"
                                       "The filter was not applied.")
            war_win.exec()

    def get_exposure(self, name_file):
        ext = name_file.split(".")[-1]
        if ext == "jpg":
            print("sono dentro")
            exposure = pyc.getJPGExposure(name_file)
            print(exposure)
            return exposure
        else:
            return -1.0

    def add_image(self):
        path = QFileDialog.getOpenFileName(
            self,
            "Open Conv",
            "./data",
            "Image Files (*.png *.jpg *.hdr)")
        if path[0] != "":
            exposure = self.get_exposure(path[0])
            self.img_dict[path[0]] = exposure
            name_file = path[0].split("/")
            self.img_list.addItem(f"{name_file[-1]}")
            self.exp_list.addItem(f"{exposure}")
            idx = self.img_list.count()
            item = self.exp_list.item(idx-1)
            item.setFlags(item.flags() | Qt.ItemIsEditable)

    def hide_window(self):
        self.img_list.clear()
        self.hide()

    def update_infos(self, img, path, win, ldr_type):
        self.img = img
        self.path = path
        self.win = win
        self.ldr_type = ldr_type


