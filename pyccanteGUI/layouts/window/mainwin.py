from layouts.window import imgwindow as iw
from PySide6 import QtGui
from PySide6.QtGui import QResizeEvent
from PySide6.QtCore import Qt


class MainImgWindow(iw.ImageWindow):
    def __init__(self, win_width, win_height, info_layout=None):
        super().__init__(win_width, win_height, info_layout)
        self.setFixedSize(win_width, win_height)
        self.info_frame.update_text(self.img)
        self.setAlignment(Qt.AlignCenter)

    def set_img(self, new_img, hdr=False):
        # Set a new image to the window
        # new_img = the new image to set
        super().set_img(new_img, hdr)
        self.path = self.check_img_ext(hdr)
        print(f"self.path = {self.path}")
        self.info_frame.update_text(self.img)
        self.update_pixmap()

    def update_pixmap(self):
        # update_pixmap updates the pixmap of the image window
        print(f"dentro update_pixmap con {self.path}")
        new_pix_map = QtGui.QPixmap(self.path)
        new_pix_map = new_pix_map.scaled(self.size(), Qt.AspectRatioMode.KeepAspectRatio)
        self.setPixmap(new_pix_map)
        self.pix_map = new_pix_map
        self.setAlignment(Qt.AlignCenter)

    def resizeEvent(self, event: QResizeEvent):
        self.update_pixmap()

