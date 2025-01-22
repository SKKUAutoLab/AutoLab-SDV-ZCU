# AutoLab-SDV-ZCU
자동화연구실 SDV: ZCU 파트 프로젝트

## Camera_server
라즈베리파이로부터 카메라 프레임 전송받아서 DDS로 Publish 해주는 프로그램

## ddscan_gw
ROS2 시스템으로부터 전송받은 제어 정보를 CAN으로 변환하여 CAN 버스에 송신하는 게이트웨이 프로그램