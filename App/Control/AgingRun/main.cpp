#include <Comm/Global/BuildOptions.h>

int main(int argc, char* argv[]) {

    /*
    
        ID 입력

    */


    /*
        중복 실행 Check
           Aging 진행중이면 
            

    */
        
    
    /*
        현재 Aging진행중이면,  
         
            Aging을 중단시키겠습니까?  

        
            Aging을 모니터링하시겠습니까?
               yes) 진행 상태를 모니터링한다.

    */

    /*
        User가 Available Board Check

        /etc/TESys/Config/Board.list
                 B1=1
                 B2=
                 B17=1

        Board.list 에  등록된 보드와  실제 Connect된 보드 사이에  Mismatch가 있으면 Error표시 
    */

    /*
        TED Verify

           Mipi Err 읽기
           ESD Err 읽기 ( 0x4E 는  정상값  ,  8번 BIt가 High이면 ) 
           ChipID 읽기 ( Mipi Err체크)
           Flash Image Verify
           PatternApp Verify
           Static Current체크 ( VLIN1, VCI 과전류 체크)
           Regulator VREG1 전압 체크  (Power Save 모드가 ON 이면  전압 흔들림이 크다.)
    */

    /*
        JOB_00XX.py 존재 여부 체크
        JOB_00xx.py 가 없는 경우는, 기 등록된 Template를 이용해  Generation 함 
    */

    /*
        모든 보드, FileSync
        FileSync  완료후 CRC체크 
    */

    /*
        Aging 시작 
    */


    /*
        경과 시간,  예측시간 
    */


    return 0;
}