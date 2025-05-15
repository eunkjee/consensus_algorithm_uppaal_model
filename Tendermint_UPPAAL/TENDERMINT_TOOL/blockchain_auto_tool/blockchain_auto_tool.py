import sys
import xml.etree.ElementTree as ET
from PyQt5.QtWidgets import QApplication, QWidget, QMainWindow, QAction, QGridLayout, QLabel, QPushButton, QLineEdit, QTextEdit, QTabWidget, QVBoxLayout, QHBoxLayout, QDialog, QMessageBox, qApp
from PyQt5.QtGui import QIcon

original_file_location = './origin/init_file.xml'
save_file_location = './save/'

x_crd = 300
y_crd = 300
x_size = 700
y_size = 500

class MySetting(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        grid = QGridLayout()
        self.setLayout(grid)

        self.lbl1 = QLabel('input number of total node:')
        self.te1 = QLineEdit()

        self.lbl2 = QLabel('input number of faulty node:')
        self.te2 = QLineEdit()

        self.lbl3 = QLabel('input voting power set:')
        self.te3 = QLineEdit()

        self.lbl4 = QLabel('Save XML File Name:')
        self.te4 = QLineEdit()

        saveButton = QPushButton('Save')
        resetButton = QPushButton('Reset')
        
        saveButton.clicked.connect(self.save_event)
        resetButton.clicked.connect(self.reset_event)

        grid.addWidget(self.lbl1, 0, 0)
        grid.addWidget(self.lbl2, 1, 0)
        grid.addWidget(self.lbl3, 2, 0)
        grid.addWidget(self.lbl4, 3, 0)

        grid.addWidget(self.te1, 0, 1)
        grid.addWidget(self.te2, 1, 1)
        grid.addWidget(self.te3, 2, 1)
        grid.addWidget(self.te4, 3, 1)
        
        grid.addWidget(resetButton)
        grid.addWidget(saveButton)

        self.setWindowTitle('Initial Setting')
        self.setGeometry(x_crd, y_crd, x_size, y_size)
        self.show()

    def showDialog(self):
        dg = QMessageBox()
        dg.setText("save completed!")
        dg.exec_()

    def reset_event(self):
        self.te1.setText('')
        self.te2.setText('')
        self.te3.setText('')
        self.te4.setText('')

    def save_event(self):
        num_node = self.te1.text()
        num_bz_node = self.te2.text()
        vp_set = self.te3.text()
        file_name = self.te4.text()

        vp_list = vp_set.split()

        targetDir = save_file_location + file_name + ".xml"

        tree = ET.parse(original_file_location)
        root = tree.getroot()

        file_text = root[0].text

        #total node
        file_text = file_text.replace("const int N = 0;", "const int N = " + str(num_node) + ";")

        #byzantine node
        file_text = file_text.replace("const int F = 0;", "const int F = " + str(num_bz_node) + ";")

        #initial setting
        tickready = "bool tickReady[N] = {"
        for i in range(int(num_node)-1):
            tickready = tickready + "true, "
        tickready = tickready + "true};"
        file_text = file_text.replace("bool tickReady[N] = {};", tickready)

        cnt_priority = "int[-PRIGAP, PRIGAP] cnt_priority[N] = {"
        for i in range(int(num_node)-1):
            cnt_priority = cnt_priority + "0, "
        cnt_priority = cnt_priority + "0};"
        file_text = file_text.replace("int[-PRIGAP, PRIGAP] cnt_priority[N] = {};", cnt_priority)

        cnt_round = "int[0, INFINITY] cnt_round[N] = {"
        for i in range(int(num_node)-1):
            cnt_round = cnt_round + "0, "
        cnt_round = cnt_round + "0};"
        file_text = file_text.replace("int[0, INFINITY] cnt_round[N] = {};", cnt_round)

        cnt_locked_round = "int[-1, INFINITY] cnt_locked_round[N] = {"
        for i in range(int(num_node)-1):
            cnt_locked_round = cnt_locked_round + "-1, "
        cnt_locked_round = cnt_locked_round + "-1};"
        file_text = file_text.replace("int[-1, INFINITY] cnt_locked_round[N] = {};", cnt_locked_round)

        cnt_PoLC_round = "int[-1, INFINITY] cnt_POLC_round[N] = {"
        for i in range(int(num_node)-1):
            cnt_PoLC_round = cnt_PoLC_round + "-1, "
        cnt_PoLC_round = cnt_PoLC_round + "-1};"
        file_text = file_text.replace("int[-1, INFINITY] cnt_POLC_round[N] = {};", cnt_PoLC_round)

        cnt_propose_value = "bool cnt_propose_value[N] = {"
        for i in range(int(num_node)-1):
            cnt_propose_value = cnt_propose_value + "false, "
        cnt_propose_value = cnt_propose_value + "false};"
        file_text = file_text.replace("bool cnt_propose_value[N] = {};", cnt_propose_value)

        cnt_locked_value = "bool cnt_locked_value[N] = {"
        for i in range(int(num_node)-1):
            cnt_locked_value = cnt_locked_value + "false, "
        cnt_locked_value = cnt_locked_value + "false};"
        file_text = file_text.replace("bool cnt_locked_value[N] = {};", cnt_locked_value)

        cnt_POLC_value = "bool cnt_POLC_value[N] = {"
        for i in range(int(num_node)-1):
            cnt_POLC_value = cnt_POLC_value + "false, "
        cnt_POLC_value = cnt_POLC_value + "false};"
        file_text = file_text.replace("bool cnt_POLC_value[N] = {};", cnt_POLC_value)

        commit_Done = "bool commit_Done[N][SLOTMAX] = {"
        for i in range(int(num_node)-1):
            commit_Done = commit_Done + "{false}, "
        commit_Done = commit_Done + "{false}};"
        file_text = file_text.replace("bool commit_Done[N][SLOTMAX] = {};", commit_Done)

        commit_check = "bool commit_check[N][SLOTMAX] = {"
        for i in range(int(num_node)-1):
            commit_check = commit_check + "{false}, "
        commit_check = commit_check + "{false}};"
        file_text = file_text.replace("bool commit_check[N][SLOTMAX] = {};", commit_check)

        voting_power = "int voting_power[N] = {"
        for i in range(int(num_node)-1):
            voting_power = voting_power + vp_list[i] + ", "
        voting_power = voting_power + vp_list[int(num_node)-1] + "};"
        file_text = file_text.replace("int voting_power[N] = {};", voting_power)

        msgqueue = "MSGQueue MSG[N] = {"
        for i in range(int(num_node)-1):
            msgqueue = msgqueue + "{0, {false}, {false}, {false}}, "
        msgqueue = msgqueue + "{0, {false}, {false}, {false}}};"
        file_text = file_text.replace("MSGQueue MSG[N] = {};", msgqueue)

        tdmnode = "TDMNODE NODE[N] = {"
        for i in range(int(num_node)-1):
            tdmnode = tdmnode + "{0, 0}, "
        tdmnode = tdmnode + "{0, 0}};"
        file_text = file_text.replace("TDMNODE NODE[N] = {};", tdmnode)

        root[0].text = file_text
        tree.write(targetDir)

        self.showDialog()

class MyVerify(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        label = QLabel('make later...', self)

        vbox = QVBoxLayout()
        vbox.addWidget(label)

        self.setLayout(vbox)
        self.setWindowTitle('Verification Setting')
        self.setGeometry(x_crd, y_crd, x_size, y_size)
        self.show()

class MyWidget(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        tab1 = MySetting()
        tab2 = MyVerify()

        tabs = QTabWidget()
        tabs.addTab(tab1, 'initial setting')
        tabs.addTab(tab2, 'verification setting')

        vbox = QVBoxLayout()
        vbox.addWidget(tabs)

        self.setLayout(vbox)

        self.setWindowTitle('QTabWidget')
        self.setGeometry(x_crd, y_crd, x_size, y_size)
        self.show()

class MyApp(QMainWindow):

    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        exitAction = QAction(QIcon('./icon/exit.png'), 'Exit', self)
        exitAction.setShortcut('Ctrl+Q')
        exitAction.setStatusTip('Exit application')
        exitAction.triggered.connect(qApp.quit)

        self.statusBar()

        self.toolbar = self.addToolBar('Exit')
        self.toolbar.addAction(exitAction)

        self.setWindowTitle('tendermint tool')
        self.setWindowIcon(QIcon('./icon/icon.png'))
        self.statusBar().showMessage('beta version V1.01')

        wg = MyWidget()
        self.setCentralWidget(wg)

        self.setGeometry(x_crd, y_crd, x_size, y_size)
        self.show()


if __name__ == '__main__':
   app = QApplication(sys.argv)
   ex = MyApp()
   sys.exit(app.exec_())