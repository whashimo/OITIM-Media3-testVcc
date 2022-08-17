#include "opencv2/opencv.hpp"
#include "sharemem.h"
#include <Windows.h>
#include <stdio.h>
using namespace std;
using namespace cv;

MMD_CAMERA *mmd_camera;
 
int main(){

  SetConsoleOutputCP(CP_UTF8);/*コンソールをUTF-8にする*/
  setvbuf(stdout, nullptr, _IOFBF, 2); /* バッファリングに必要 */

  mmd_camera = Getshare();/* 共有メモリの取得 */

  Mat img= imread("test.jpg");
  imshow("test",img); 
  while(1){
    if(mmd_camera->event[0]!='\0')
      printf("MMDevent: %s\n", mmd_camera->event);

    int key = waitKey(30);

    if(key == 'q' || key == 27){
      break;
    }else if (key == '0'){
     sprintf_s(mmd_camera->camera, "keyboard_0");
    }
    if(mmd_camera->camera[0]!='\0')
      printf("MMDcamera: %s\n", mmd_camera->camera);
  }
  Closeshare(mmd_camera);
  destroyAllWindows();
  return 0;
}