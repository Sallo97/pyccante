# This file contains the InfoFrame class
from layouts import lines
from PySide6.QtWidgets import QVBoxLayout, QLabel, QFrame
from PySide6.QtCore import Qt


class InfoFrame(QFrame):
    # InfoFrames defines a QFrame that displays
    # information about the current image read.
    def __init__(self):
        super(InfoFrame, self).__init__()

        # Define size parameters.
        # These parameters are contained in a sub-layout
        # called dim_layout.
        self.info_tile = QLabel("Image Info")
        self.info_tile.setAlignment(Qt.AlignCenter)
        self.height_label = QLabel()
        self.height_label.setFixedSize(200, 20)
        self.width_label = QLabel()
        self.width_label.setFixedSize(200, 20)
        self.size_label = QLabel()
        self.size_label.setFixedSize(100, 20)
        dim_layout = QVBoxLayout()
        dim_layout.addWidget(self.info_tile)
        dim_layout.addWidget(self.width_label)
        dim_layout.addWidget(self.height_label)
        dim_layout.addWidget(self.size_label)
        dim_layout.addWidget(lines.get_h_line())

        # Define maximum RGB values.
        # These parameters are contained in a sub-layout
        # called max_layout.
        self.max_title = QLabel("RGB Maximum")
        self.max_title.setAlignment(Qt.AlignCenter)
        self.maxr_label = QLabel()
        self.maxr_label.setFixedSize(100, 20)
        self.maxg_label = QLabel()
        self.maxg_label.setFixedSize(100, 20)
        self.maxb_label = QLabel()
        self.maxb_label.setFixedSize(100, 20)
        max_layout = QVBoxLayout()
        max_layout.addWidget(self.max_title)
        max_layout.addWidget(self.maxr_label)
        max_layout.addWidget(self.maxb_label)
        max_layout.addWidget(self.maxg_label)
        max_layout.addWidget(lines.get_h_line())

        # Define minimum RGB values.
        # These parameters are contained in a sub-layout
        # called min_layout.
        self.min_title = QLabel("RGB Minimum")
        self.min_title.setAlignment(Qt.AlignCenter)
        self.minr_label = QLabel()
        self.minr_label.setFixedSize(100, 20)
        self.ming_label = QLabel()
        self.ming_label.setFixedSize(100, 20)
        self.minb_label = QLabel()
        self.minb_label.setFixedSize(100, 20)
        min_layout = QVBoxLayout()
        min_layout.addWidget(self.min_title)
        min_layout.addWidget(self.minr_label)
        min_layout.addWidget(self.minb_label)
        min_layout.addWidget(self.ming_label)

        # Put the sub-layout together.
        self.info_layout = QVBoxLayout()
        self.info_layout.addLayout(dim_layout)
        self.info_layout.addLayout(max_layout)
        self.info_layout.addLayout(min_layout)

        self.setLayout(self.info_layout)
        self.setFixedHeight(300)

    def update_text(self, img):
        # Update the text of the labels.
        # img = the new image to get the new info.
        self.width_label.setText(f"W : {img.width} px")
        self.height_label.setText(f"H : {img.height} px")
        self.size_label.setText(f"S : {img.size()} px")

        max_rgb = img.getMaxVal()
        self.maxr_label.setText(f"R : {max_rgb[0]}")
        self.maxg_label.setText(f"G : {max_rgb[1]}")
        self.maxb_label.setText(f"B : {max_rgb[2]}")

        min_rgb = img.getMinVal()
        self.minr_label.setText(f"R : {min_rgb[0]}")
        self.ming_label.setText(f"G : {min_rgb[1]}")
        self.minb_label.setText(f"B : {min_rgb[2]}")
