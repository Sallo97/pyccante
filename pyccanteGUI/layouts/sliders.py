from PySide6.QtWidgets import QVBoxLayout, QFrame, QLabel
from layouts import slider as sl, lines as ln
from PySide6.QtCore import Qt


class SlidersFrame(QFrame):
    def __init__(self, main_win, custom_win):
        super(SlidersFrame, self).__init__()
        layout = QVBoxLayout()
        exp_label = QLabel("Exposure")
        exp_label.setAlignment(Qt.AlignCenter)
        gamma_label = QLabel("Gamma")
        gamma_label.setAlignment(Qt.AlignCenter)
        layout.addWidget(exp_label)
        exp_slider = sl.Slider(-8, 8)
        exp_slider.valueChanged.connect(
            lambda:
            self.update_values(main_win, custom_win,
                               gamma_slider.value(), exp_slider.value()))
        layout.addWidget(exp_slider)
        layout.addWidget(ln.get_h_line())
        layout.addWidget(gamma_label)
        gamma_slider = sl.Slider(0, 4)
        gamma_slider.valueChanged.connect(
            lambda:
            self.update_values(main_win, custom_win,
                               gamma_slider.value(), exp_slider.value()))
        layout.addWidget(gamma_slider)
        layout.setAlignment(Qt.AlignCenter)
        self.setLayout(layout)
        self.setFixedHeight(100)

    def update_values(self, main_win, custom_win, gamma, exp):
        # Update the main e custom windows exposure value
        # and gamma value
        # main_win = the main windows
        # custom_win = the custom windows
        # value = the new exposure value
        main_win.update_sliders(gamma=gamma, exp=exp)
        custom_win.update_sliders(gamma=gamma, exp=exp)

