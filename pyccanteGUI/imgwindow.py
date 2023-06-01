from PySide6.QtWidgets import QLabel
from PySide6 import QtGui, QtWidgets
from PySide6.QtWidgets import (QSizePolicy)
from PySide6.QtCore import Qt
from PySide6.QtGui import QWheelEvent, QResizeEvent


class ImageWindow(QLabel):
    def __init__(self, path, win_width, win_height,
                 img_width, img_height,
                 w_type="custom"):
        super(ImageWindow, self).__init__()
        self.path = path
        self.width = win_width
        self.height = win_height
        self.img_width = img_width
        self.img_height = img_height
        self.res_width = img_width
        self.res_height = img_height
        self.max_width = 4500
        self.max_height = 4500
        self.min_width = 10
        self.min_height = 10
        self.zoom = 1.5
        self.pix_map = QtGui.QPixmap(self.path)
        self.w_type= w_type
        self.mouse_flag = False
        img_window = QLabel()
        if w_type == "custom":
            img_window.setMinimumSize(win_width, win_height)
        elif w_type == "main":
            img_window.setFixedSize(win_width, win_height)
        self.update_pixmap(None, None, None)

    def update_pixmap(self, img_w=None, img_h=None, new_path=None, mouse=None):
        if img_w is not None and img_h is not None:
            self.img_width = img_w
            self.img_height = img_h

        if mouse == "+" and self.max_size_cond():
            self.res_width *= self.zoom
            self.res_height *= self.zoom
        elif mouse == "-" and self.min_size_cond():
            self.res_width /= self.zoom
            self.res_height /= self.zoom
        elif self.max_size_cond() and self.min_size_cond():
            self.res_width = self.img_width
            self.res_height = self.img_height
            while self.res_width > self.width or self.res_height > self.height:
                self.res_width /= self.zoom
                self.res_height /= self.zoom

        if new_path is not None:
            self.path = new_path

        # print(f"Dentro {self.w_type}\n"
        #      f"width: {self.width} height: {self.height}"
        #      f"\nimg_width: {self.pixmap().width()} img_height: {self.pixmap().height()}"
        #      f"\nres_width: {self.res_width} res_height: {self.res_height}")

        new_pix_map = QtGui.QPixmap(self.path)

        if self.w_type == "main":
            new_pix_map = new_pix_map.scaled(self.size(), Qt.AspectRatioMode.KeepAspectRatio)
        else:

            new_pix_map = new_pix_map.scaled(self.res_width, self.res_height,
                                             Qt.AspectRatioMode.KeepAspectRatioByExpanding)
        self.pix_map = new_pix_map
        self.setPixmap(self.pix_map)
        self.setAlignment(Qt.AlignCenter)

    def wheelEvent(self, event: QWheelEvent):
        if self.w_type == "custom":
            if event.angleDelta().y() > 0:
                self.update_pixmap(None, None, None, "+")
            else:
                self.update_pixmap(None, None, None, "-")
            self.mouse_flag = True

    def resizeEvent(self, event: QResizeEvent):
        super().resizeEvent(event)
        if self.w_type == "main":
            self.update_pixmap(None, None, None)
        elif self.w_type == "custom" and self.mouse_flag is False:
            self.update_pixmap(None, None, None)

    def max_size_cond(self):
        return self.res_width <= self.max_width or \
               self.res_height <= self.max_height

    def min_size_cond(self):
        return self.res_width >= self.min_width or \
               self.res_height >= self.min_height

    def original_size(self):
        self.mouse_flag = False
        self.res_width = self.img_width
        self.res_height = self.img_height
        self.update_pixmap(None, None, None)