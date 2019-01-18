1. 學號：b04901117
2. 姓名：毛弘仁
3. 使用之程式語言：< C++ >
4. 使用之編譯器：g++ (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609
5. 檔案壓縮方式: <unzip b04901117_p3_v1.zip>
6. 各檔案說明：
	 router 這個 executable binary 為 Linux (Ubuntu 16.04 LTS) 環境編譯後的執行檔
	 src/ 底下為原始碼，我在 main.cpp 以及 graph.h 都有自己寫東西
	 report.doc 為報告

7. 編譯方式說明：        	
	 在 command line 執行 g++ -std=c++11 -O3 src/main.cpp src/parser.cpp -o router
	 即可編譯出 router 這個 executable binary

8. 執行、使用方式說明：
	 在 command line 輸入 ./router <input_file_path> <output_file_path>
	 例如：./router benchmarks/gr20x20.in 20x20.out 
