#include <Comm/Global/BuildOptions.h>

int main(int argc, char* argv[]) {

    /*
    
        ID �Է�

    */


    /*
        �ߺ� ���� Check
           Aging �������̸� 
            

    */
        
    
    /*
        ���� Aging�������̸�,  
         
            Aging�� �ߴܽ�Ű�ڽ��ϱ�?  

        
            Aging�� ����͸��Ͻðڽ��ϱ�?
               yes) ���� ���¸� ����͸��Ѵ�.

    */

    /*
        User�� Available Board Check

        /etc/TESys/Config/Board.list
                 B1=1
                 B2=
                 B17=1

        Board.list ��  ��ϵ� �����  ���� Connect�� ���� ���̿�  Mismatch�� ������ Errorǥ�� 
    */

    /*
        TED Verify

           Mipi Err �б�
           ESD Err �б� ( 0x4E ��  ����  ,  8�� BIt�� High�̸� ) 
           ChipID �б� ( Mipi Errüũ)
           Flash Image Verify
           PatternApp Verify
           Static Currentüũ ( VLIN1, VCI ������ üũ)
           Regulator VREG1 ���� üũ  (Power Save ��尡 ON �̸�  ���� ��鸲�� ũ��.)
    */

    /*
        JOB_00XX.py ���� ���� üũ
        JOB_00xx.py �� ���� ����, �� ��ϵ� Template�� �̿���  Generation �� 
    */

    /*
        ��� ����, FileSync
        FileSync  �Ϸ��� CRCüũ 
    */

    /*
        Aging ���� 
    */


    /*
        ��� �ð�,  �����ð� 
    */


    return 0;
}