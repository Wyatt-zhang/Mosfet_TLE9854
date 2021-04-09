import sys

from PySide2.QtWidgets import QApplication
from PySide2.QtUiTools import QUiLoader


import PLinApi
import collections
from ctypes import *



class mywindow:
    def __init__(self):
        super(mywindow, self).__init__()

        #GUI 动态载入
        self.ui = QUiLoader().load('u1.ui')


        #Lin通讯有关参数初始化
        self.hardwareInit()

        #部件逻辑初始化
        self.widgetsInit()

    def test(self):
        pass

    def widgetsInit(self):
        #按键按下逻辑

        #刷新动作
        self.ui.pushBtn_refresh.clicked.connect(self.refreshHardware)

        self.ui.cbBox_hardware.activated.connect(self.test)

        #连接动作，断开
        self.ui.pushBtn_connect.clicked.connect(self.linConnect)
        self.ui.pushBtn_disconnect.clicked.connect(self.doLinDisconnect)

        #车窗运动命令
        self.ui.radioBtn_manualup.toggled.connect(self.linMsgSend)
        self.ui.radioBtn_manualdown.toggled.connect(self.linMsgSend)
        self.ui.radioBtn_autoup.toggled.connect(self.linMsgSend)
        self.ui.radioBtn_autodown.toggled.connect(self.linMsgSend)
        self.ui.radioBtn_nocmd.toggled.connect(self.linMsgSend)

    def hardwareInit(self):


        # 创建一个实例 自动load PLIN-API
        self.m_objPLinApi = PLinApi.PLinApi()
        if (not self.m_objPLinApi.isLoaded()):
            print("当前目录下没有dll文件，加载失败")
            raise Exception("PLin-API could not be loaded ! Exiting...")

        # configure LIN variables
        self.m_hClient = PLinApi.HLINCLIENT(0)
        self.m_hHw = PLinApi.HLINHW(0)
        self.m_HwMode = PLinApi.TLIN_HARDWAREMODE_NONE
        self.m_HwBaudrate = c_ushort(0)
        self.FRAME_FILTER_MASK = c_uint64(0xFFFFFFFFFFFFFFFF)
        self.m_lMask = self.FRAME_FILTER_MASK

        # LIN GUI variables

        # sorted dictionnary of available hardware
        d = {'<No available harware>': PLinApi.HLINHW(0)}
        self.m_dataHws = collections.OrderedDict(
            sorted(list(d.items()), key=lambda t: t[0]))
        self.ui.cbBox_hardware.addItem('<No available harware>')
        self.ui.cbBox_hardware.setCurrentIndex(0)

        # sorted dictionnary of hardware baudrates
        d = {'2400': 2400, '9600': 9600, '10400': 10400, '19200': 19200}
        self.m_dataHwBaudrates = collections.OrderedDict(
            sorted(list(d.items()), key=lambda t: t[1]))
        for name in self.m_dataHwBaudrates.keys():
            self.ui.cbBox_buadrate.addItem(name)
        self.ui.cbBox_buadrate.setCurrentIndex(3)

        # sorted dictionary of hardware mode
        d = {'Master': PLinApi.TLIN_HARDWAREMODE_MASTER,
             'Slave': PLinApi.TLIN_HARDWAREMODE_SLAVE}
        self.m_dataHwModes = collections.OrderedDict(
            sorted(list(d.items()), key=lambda t: t[0]))
        for name in self.m_dataHwModes.keys():
            self.ui.cbBox_mode.addItem(name)
        self.ui.cbBox_mode.setCurrentIndex(0)
        # LIN Global Frame Table
        '''
        self.m_pGFT = CGlobalFrameTable(
            self.m_objPLinApi, self.m_hClient, self.m_hHw, self.m_HwMode, self.m_lMask)
            '''
        # LIN message receive queue
        self.m_LastMsgsList = []

    def refreshHardware(self):
        """
        Fills combobox  with available LIN hardware

        Returns:
            None
        """
        # Get the buffer length needed...
        lwCount = c_ushort(0)
        availableHWs = (PLinApi.HLINHW * 0)()
        linResult = self.m_objPLinApi.GetAvailableHardware(availableHWs, 0, lwCount)
        if (lwCount == 0):
            # use default value if either no hw is connected or an unexpected error occured
            lwCount = c_ushort(16);
        availableHWs = (PLinApi.HLINHW * lwCount.value)()
        lwBuffSize = c_ushort(lwCount.value * 2)

        # Get all available LIN hardware.
        linResult = self.m_objPLinApi.GetAvailableHardware(
            availableHWs, lwBuffSize, lwCount)
        '''
        获取可用的硬件信息
        '''
        if (linResult == PLinApi.TLIN_ERROR_OK):

            # clear combobox
            self.ui.cbBox_hardware.clear()
            self.m_dataHws.clear()

            # Get information for each LIN hardware found
            lnHwType = c_int(0)
            lnDevNo = c_int(0)
            lnChannel = c_int(0)
            lnMode = c_int(0)

            #把硬件信息加入下拉框中
            if (lwCount.value == 0):
                '''
                如果没发现可用的硬件连接
                '''
                strHw = '<No Hardware found>'
                self.ui.cbBox_hardware.addItem(strHw)
                self.m_dataHws[strHw] = PLinApi.HLINHW(0)
            else:
                self.ui.pushBtn_connect.setEnabled(True)
                for i in range(lwCount.value):

                    lwHw = availableHWs[i]

                    # Read the type of the hardware with the handle lwHw.
                    self.m_objPLinApi.GetHardwareParam(
                        lwHw, PLinApi.TLIN_HARDWAREPARAM_TYPE, lnHwType, 0)

                    # Read the device number of the hardware with the handle
                    # lwHw.
                    self.m_objPLinApi.GetHardwareParam(
                        lwHw, PLinApi.TLIN_HARDWAREPARAM_DEVICE_NUMBER, lnDevNo, 0)

                    # Read the channel number of the hardware with the handle
                    # lwHw.
                    self.m_objPLinApi.GetHardwareParam(
                        lwHw, PLinApi.TLIN_HARDWAREPARAM_CHANNEL_NUMBER, lnChannel, 0)

                    # Read the mode of the hardware with the handle lwHw (Master,
                    # Slave or None).
                    self.m_objPLinApi.GetHardwareParam(
                        lwHw, PLinApi.TLIN_HARDWAREPARAM_MODE, lnMode, 0)
                    #没有连接 所以读取的信息是没有模式的
                    #print(lnMode.value)

                    # translate type value to string
                    if (lnHwType.value == PLinApi.LIN_HW_TYPE_USB_PRO.value):
                        strName = "PCAN-USB Pro"
                    elif (lnHwType.value == PLinApi.LIN_HW_TYPE_USB_PRO_FD.value):
                        strName = "PCAN-USB Pro FD"
                    elif (lnHwType.value == PLinApi.LIN_HW_TYPE_PLIN_USB.value):
                        strName = "PLIN-USB"
                    else:
                        strName = "Unknown"

                    # add information to channel combobox
                    strHw = str.format(
                        '{0} - dev. {1}, chan. {2}', strName, lnDevNo.value, lnChannel.value)
                    self.ui.cbBox_hardware.addItem(strHw)

                    '''
                    这里很重要,把可连接的硬件名字 存入数组
                    '''
                    self.m_dataHws[strHw] = PLinApi.HLINHW(lwHw)
            # select first item
            self.ui.cbBox_hardware.setCurrentIndex(0)
            print(self.ui.cbBox_hardware.currentText())
        else:
            print('调用PlinApi函数失败！')

    def linMsgSend(self):
        """
        ComboBox cbbID selection changed handler

        Returns:
            None
        """
        # Assert that a frame ID has been selected
        # Get the CFrameDefinition associated to the selected FrameID

        '''
        frame = None
        try:
            frameId = int(self.cbbID['selection'], 16)
            frame = self.m_pGFT.m_lFrameDefinitions[frameId]
        except:
            self.cbbID.focus()
            return
        '''

        '''
        发送，master 模式，帧ID 1c,数据域8字节
        '''

        pMsg = PLinApi.TLINMsg()

        #此处为PID 不是帧ID 对应帧ID 1C
        pMsg.FrameId = c_ubyte(156)
        pMsg.Direction = PLinApi.TLINDirection(1)
        pMsg.ChecksumType = PLinApi.TLINChecksumType(2)
        pMsg.Length = c_ubyte(8)

        if(self.ui.radioBtn_autodown.isChecked()):
            self.m_Data2TXT = '40'
        elif(self.ui.radioBtn_manualup.isChecked()):
            self.m_Data2TXT = '10'
        elif(self.ui.radioBtn_manualdown.isChecked()):
            self.m_Data2TXT = '20'
        elif(self.ui.radioBtn_autoup.isChecked()):
            self.m_Data2TXT = '30'
        elif(self.ui.radioBtn_nocmd.isChecked()):
            self.m_Data2TXT = '00'
        else:
            self.m_Data2TXT = '00'

        self.m_Data0TXT = '00'
        self.m_Data1TXT = '00'
       # self.m_Data2TXT = '10'
        self.m_Data3TXT = '00'
        self.m_Data4TXT = '00'
        self.m_Data5TXT = '11'
        self.m_Data6TXT = '00'
        self.m_Data7TXT = '00'

        # fill data
        edits = [
            self.m_Data0TXT, self.m_Data1TXT, self.m_Data2TXT, self.m_Data3TXT,
            self.m_Data4TXT, self.m_Data5TXT, self.m_Data6TXT, self.m_Data7TXT]

        #不超过上限 0~7
        #转换为由16进制转为10进制整形
        for i in range(0,8):
            pMsg.Data[i] = c_ubyte(int(edits[i], 16))
            #print(pMsg.Data[i])

        # Check if the hardware is initialized as master
        if (self.m_HwMode.value == PLinApi.TLIN_HARDWAREMODE_MASTER.value):
            # Calculate the checksum contained with the
            # checksum type that was set some line before.
           # print('send')
            linResult = self.m_objPLinApi.CalculateChecksum(pMsg)
          #  print(linResult)
            # Try to send the LIN frame message with LIN_Write.
            linResult = self.m_objPLinApi.Write(self.m_hClient, self.m_hHw, pMsg)
           # print(linResult)

    def linConnect(self):
        """
        Connects to a LIN hardware.

        Returns:
            True if connection is successful, False otherwise
        """
        result = False
        if (self.m_hHw.value != 0):
            # If a connection to hardware already exits
            # disconnect this connection first.
            if (not self.doLinDisconnect()):
                print('Link is already existing')
                return result

        if (self.m_hClient.value == 0):
            # register LIN client
            self.m_objPLinApi.RegisterClient(
                "PLIN-API Example", None, self.m_hClient)

        # Try to connect the application client to the hardware with the local
        # handle.
        #当前选中要连接的硬件型号
        hwHandle = self.m_dataHws[self.ui.cbBox_hardware.currentText()]
        #开始连接
        linResult = self.m_objPLinApi.ConnectClient(self.m_hClient, hwHandle)

        if (linResult == PLinApi.TLIN_ERROR_OK):

            self.ui.groupBox_Action.setEnabled(True)
            # If the connection successfull assign
            # the local handle to the member handle.
            self.m_hHw = hwHandle
           # print('lianjiechengg')
            # read hardware's parameter mode and baudrate
            lnMode = c_int(0)
            lnCurrBaud = c_int(0)
            linResult = self.m_objPLinApi.GetHardwareParam(
                hwHandle, PLinApi.TLIN_HARDWAREPARAM_MODE, lnMode, 0)
            linResult = self.m_objPLinApi.GetHardwareParam(
                hwHandle, PLinApi.TLIN_HARDWAREPARAM_BAUDRATE, lnCurrBaud, 0)

            # check if initialization is required
            #Mode selection Master or slave
            #注意这里是字典，键为字符
            hwMode = self.m_dataHwModes[self.ui.cbBox_mode.currentText()]

            #baudrate selection
            try:
                # convert baudrates selection to int
                hwBaudrate = c_ushort(int(self.ui.cbBox_buadrate.currentText()))
            except:
                hwBaudrate = c_ushort(0)

            if (lnMode.value == PLinApi.TLIN_HARDWAREMODE_NONE.value or lnCurrBaud.value != hwBaudrate.value):
                # Only if the current hardware is not initialized
                # try to Initialize the hardware with mode and baudrate
                linResult = self.m_objPLinApi.InitializeHardware(
                    self.m_hClient, self.m_hHw, hwMode, hwBaudrate)
                #print('连接成功')

            if (linResult == PLinApi.TLIN_ERROR_OK):
                self.m_HwMode = hwMode
                self.m_HwBaudrate = hwBaudrate
                # Set the client filter with the mask.
                #print('ewerwer')
                linResult = self.m_objPLinApi.SetClientFilter(
                    self.m_hClient, self.m_hHw, self.m_lMask)
                # Read the frame table from the connected hardware.
                # self.readFrameTableFromHw()
                # Reset the last LIN error code to default.
                linResult = PLinApi.TLIN_ERROR_OK
                result = True
            else:
                # An error occured while initializing hardware.
                # Set the member variable to default.
                self.m_hHw = PLinApi.HLINHW(0)
                result = False
        else:
            # The local hardware handle is invalid
            # and/or an error occurs while connecting
            # hardware with client.
            # Set the member variable to default.
            self.m_hHw = PLinApi.HLINHW(0)
            result = False
        if (linResult != PLinApi.TLIN_ERROR_OK):
            self.showMessageError(linResult)
        return result

    # Disconnects an existing connection to a LIN hardware

    def doLinDisconnect(self):
        # If the application was registered with LIN as client.
        if (self.m_hHw.value != 0):
            # The client was connected to a LIN hardware.
            # Before disconnect from the hardware check
            # the connected clients and determine if the
            # hardware configuration have to reset or not.
            #
            # Initialize the locale variables.
            lfOtherClient = False
            lfOwnClient = False
            lhClientsSize = c_ushort(255)
            lhClients = (PLinApi.HLINCLIENT * lhClientsSize.value)()
            # Get the connected clients from the LIN hardware.
            linResult = self.m_objPLinApi.GetHardwareParam(
                self.m_hHw, PLinApi.TLIN_HARDWAREPARAM_CONNECTED_CLIENTS, lhClients, lhClientsSize)
            if (linResult == PLinApi.TLIN_ERROR_OK):
                # No errors !
                # Check all client handles.
                for i in range(1, lhClientsSize.value):
                    # If client handle is invalid
                    if (lhClients[i] == 0):
                        continue
                    # Set the boolean to true if the handle isn't the
                    # handle of this application.
                    # Even the boolean is set to true it can never
                    # set to false.
                    lfOtherClient = lfOtherClient | (
                        lhClients[i] != self.m_hClient.value)
                    # Set the boolean to true if the handle is the
                    # handle of this application.
                    # Even the boolean is set to true it can never
                    # set to false.
                    lfOwnClient = lfOwnClient | (
                        lhClients[i] == self.m_hClient.value)
            # If another application is also connected to
            # the LIN hardware do not reset the configuration.
            if (lfOtherClient == False):
                # No other application connected !
                # Reset the configuration of the LIN hardware.
                linResult = self.m_objPLinApi.ResetHardwareConfig(
                    self.m_hClient, self.m_hHw)
            # If this application is connected to the hardware
            # then disconnect the client. Otherwise not.
            if (lfOwnClient == True):
                # Disconnect if the application was connected to a LIN
                # hardware.
                linResult = self.m_objPLinApi.DisconnectClient(
                    self.m_hClient, self.m_hHw)
                if (linResult == PLinApi.TLIN_ERROR_OK):
                    self.m_hHw = PLinApi.HLINHW(0)
                    return True
                else:
                    # Error while disconnecting from hardware.
                    self.showMessageError(linResult)
                    return False
            else:
                return True
        else:
            # m_hHw not connected
            return True
if __name__ == '__main__':
    app = QApplication(sys.argv)
    demo = mywindow()
    demo.ui.show()
    sys.exit(app.exec_())