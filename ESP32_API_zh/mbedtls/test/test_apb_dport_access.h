/* 当其他CPU执行某组DPORT访问时，测试APB访问是否仍然安全的实用程序功能

   （有关详细信息，请参阅ECO 3.10和独立的esp32 test_dport.c）。
*/

/* start_apb_access_loop（）在非Unity测试CPU上的循环中启动从apb读取的任务。

   在执行涉及DPORT读取的操作之前调用此命令。

   在unicore模式下不执行任何操作。
*/
void start_apb_access_loop(void);

/* verify_apb_access_loop（）终止由start_apb_aaccess_loop启动的任务，并验证所有apb读取均未被不安全的DPORT读取损坏。
*/
void verify_apb_access_loop(void);

