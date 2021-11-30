## 易错点记录

- regex：regex_match: pattern必需匹配到整个源string，才会返回true
- 简单数组,array, vector 在不同场景下的各有优缺点
- 数组与指针？
- 打开文件：运行命令行的当前目录为根目录。
- 结构体数组的大小会很容易就溢出，在大于10000的时候就报错；并且内部的数组成员初始化大小也很容易溢出.


- 打开文件，文件不存在（比如文件名写错）的时候，不会报错，默默地什么都不做：没有很好地异常处理设计。。
- Boost库的安装：Homebrew方式，Boost库要求c++11以上，所以g++ 命令需要加参数 -std=c++11
- boost::regex, 捕获等：[https://www.boost.org/doc/libs/1_46_1/libs/regex/doc/html/boost_regex/captures.html]

- 二维数组指针的使用；（./data-structures/graph/graph.cpp）
- 结构体传参数时，只会进行浅拷贝，即int,float,指针等，数组则不会进行深拷贝。
