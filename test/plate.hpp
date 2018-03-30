#ifndef EASYPR_PLATE_HPP
#define EASYPR_PLATE_HPP

#include "easypr/network/server_socket.hpp"
#include "easypr/network/networkConfig.hpp"

extern struct senddata sdata;

namespace easypr {

namespace demo {

using namespace cv;
using namespace std;

int test_plate_locate() {
  cout << "test_plate_locate" << endl;

  const string file = "result.jpg";

  cv::Mat src = imread(file);

  vector<cv::Mat> resultVec;
  CPlateLocate plate;
  //plate.setDebug(0);
  //plate.setLifemode(true);

  int result = plate.plateLocate(src, resultVec);
  if (result == 0) {
    size_t num = resultVec.size();
    for (size_t j = 0; j < num; j++) {
      cv::Mat resultMat = resultVec[j];
      imshow("plate_locate", resultMat);
      waitKey(0);
    }
    destroyWindow("plate_locate");
  }

  return result;
}

int test_plate_judge() {
  cout << "test_plate_judge" << endl;

  cv::Mat src = imread("result.jpg");

  vector<cv::Mat> matVec;
  vector<cv::Mat> resultVec;

  CPlateLocate lo;
  lo.setDebug(1);
  lo.setLifemode(true);

  int resultLo = lo.plateLocate(src, matVec);

  if (0 != resultLo) return -1;

  cout << "plate_locate_img" << endl;
  size_t num = matVec.size();
  for (size_t j = 0; j < num; j++) {
    Mat resultMat = matVec[j];
    imshow("plate_judge", resultMat);
    waitKey(0);
  }
  destroyWindow("plate_judge");

  int resultJu = PlateJudge::instance()->plateJudge(matVec, resultVec);

  if (0 != resultJu) return -1;

  cout << "plate_judge_img" << endl;
  num = resultVec.size();
  for (size_t j = 0; j < num; j++) {
    Mat resultMat = resultVec[j];
    imshow("plate_judge", resultMat);
    waitKey(0);
  }
  destroyWindow("plate_judge");

  return resultJu;
}

int test_plate_detect() {
  cout << "test_plate_detect" << endl;

  cv::Mat src = imread("result.jpg");

  vector<CPlate> resultVec;
  CPlateDetect pd;
  pd.setPDLifemode(true);

  int result = pd.plateDetect(src, resultVec);
  if (result == 0) {
    size_t num = resultVec.size();
    for (size_t j = 0; j < num; j++) {
      CPlate resultMat = resultVec[j];

      imshow("plate_detect", resultMat.getPlateMat());
      waitKey(0);
    }
    destroyWindow("plate_detect");
  }

  return result;
}

int test_plate_recognize() {
  cout << "test_plate_recognize_video" << endl;
  //Mat src = imread("resources/image/test.jpg");
  Mat src = imread("result.jpg");
  CPlateRecognize pr;
  pr.setLifemode(true);
  pr.setDebug(false);
  pr.setMaxPlates(4);
  //pr.setDetectType(PR_DETECT_COLOR | PR_DETECT_SOBEL);
  pr.setDetectType(easypr::PR_DETECT_CMSER);

  //vector<string> plateVec;
  vector<CPlate> plateVec;

  int result = pr.plateRecognize(src, plateVec);
  //int result = pr.plateRecognizeAsText(src, plateVec);
  if (result == 0) {
    size_t num = plateVec.size();
    for (size_t j = 0; j < num; j++) {
      cout << "plateRecognize: " << plateVec[j].getPlateStr() << endl;
    }
  }

  if (result != 0) cout << "result:" << result << endl;

  return result;
}


int test_plate_recognize(Mat src) {
    cout << "test_plate_recognize" << endl;

    CPlateRecognize pr; 
    pr.setLifemode(true);
    pr.setDebug(false);
    pr.setMaxPlates(4);
    //pr.setDetectType(PR_DETECT_COLOR | PR_DETECT_SOBEL);
    pr.setDetectType(easypr::PR_DETECT_CMSER);

    //vector<string> plateVec;
    vector<CPlate> plateVec;

    int result = pr.plateRecognize(src, plateVec);
    //int result = pr.plateRecognizeAsText(src, plateVec);
    if (result == 0) {
        size_t num = plateVec.size();
        for (size_t j = 0; j < num; j++) {
        cout << "plateRecognize: " << plateVec[j].getPlateStr() << endl;
        strcpy(sdata.VALID_DATA,plateVec[j].getPlateStr().c_str());
        sdata.CHECK_SUM=crc8((uint8_t *)&sdata,24);
        broadcast_data((char *)&sdata,25);
        for( uint k = 0; k < 16; k++)
        {
            printf( "plate %02x\n",sdata.VALID_DATA[k]);    
        }
        }
    }   

    if (result != 0) cout << "result:" << result << endl;

    return result;
}

#if 0
int test_plate_recognize() {
  cout << "test_plate_recognize" << endl;

  Mat src = imread("result.jpg");

  CPlateRecognize pr;
  pr.setLifemode(true);
  pr.setDebug(false);
  pr.setMaxPlates(1);
  //pr.setDetectType(PR_DETECT_COLOR | PR_DETECT_SOBEL);
  pr.setDetectType(easypr::PR_DETECT_CMSER);

  //vector<string> plateVec;
  vector<CPlate> plateVec;

  int result = pr.plateRecognize(src, plateVec);
  //int result = pr.plateRecognizeAsText(src, plateVec);
  if (result == 0) {
    size_t num = plateVec.size();
    for (size_t j = 0; j < num; j++) {
      cout << "plateRecognize: " << plateVec[j].getPlateStr() << endl;
    }
  }

  if (result != 0) cout << "result:" << result << endl;

  return result;
}
#endif
}
}

#endif  // EASYPR_PLATE_HPP
