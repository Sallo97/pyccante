from layouts.window import imgwindow as iw
from PySide6 import QtGui
from PySide6.QtCore import Qt
from PySide6.QtGui import QWheelEvent, QResizeEvent
from utils import path


class CustomImgWindow(iw.ImageWindow):
    def __init__(self, win_width, win_height, info_layout=None):
        super().__init__(win_width, win_height, info_layout)
        self.setMinimumSize(win_width, win_height)
        self.mouse_flag = False

        # Set parameters to implement the zoom
        self.res_width = self.img.width
        self.res_height = self.img.height
        self.max_width = 4500
        self.max_height = 4500
        self.min_width = 10
        self.min_height = 10
        self.zoom = 1.5

        self.update_pixmap("")

    def resizeEvent(self, event: QResizeEvent):
        if self.mouse_flag is False:
            self.update_pixmap("")

    def max_size_cond(self):
        return self.res_width <= self.max_width or \
            self.res_height <= self.max_height

    def min_size_cond(self):
        return self.res_width >= self.min_width or \
            self.res_height >= self.min_height

    def original_size(self):
        self.mouse_flag = False
        self.res_width = self.img.width
        self.res_height = self.img.height
        self.update_pixmap("")

    def wheelEvent(self, event: QWheelEvent):
        if event.angleDelta().y() > 0:
            self.update_pixmap("+")
        else:
            self.update_pixmap("-")
        self.mouse_flag = True

    def update_pixmap(self, mouse=""):
        # update_pixmap updates the pixmap of the image window
        # mouse = checks if the mouse wheel has been moved and
        #         resize the image accordingly

        # Check if the mouse wheel has been moved
        if mouse == "+" and self.max_size_cond():
            self.res_width *= self.zoom
            self.res_height *= self.zoom
        elif mouse == "-" and self.min_size_cond():
            self.res_width /= self.zoom
            self.res_height /= self.zoom
        elif self.max_size_cond() and self.min_size_cond():
            self.res_width = self.img.width
            self.res_height = self.img.height
            # Resize the image to the window size
            while self.res_width > self.width or self.res_height > self.height:
                self.res_width /= self.zoom
                self.res_height /= self.zoom

        # Set a new pix_map
        print(f"Dentro custom_win update pixmap con\nself.path= {self.path}")
        new_pix_map = QtGui.QPixmap(self.path)
        new_pix_map = new_pix_map.scaled(self.res_width, self.res_height,
                                         Qt.AspectRatioMode.KeepAspectRatioByExpanding)
        self.pix_map = new_pix_map
        self.setPixmap(self.pix_map)
        self.setAlignment(Qt.AlignCenter)

    def set_img(self, new_img, hdr=False):
        super().set_img(new_img, hdr)
        self.path = self.check_img_ext(hdr)
        self.update_pixmap()
        
    def check_img_ext(self, hdr):
        new_path = super().check_img_ext(hdr)
        if hdr is False:
            print(f"Sono qui con hdr = {hdr}")
            new_path = path.get_custom_path()
            self.img.Write(new_path, self.ldr_type)
        return new_path

    def get_ldr(self):
        return self.ldr_type

