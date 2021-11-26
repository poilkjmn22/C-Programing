# cli args: 
# @cate: data-structure category
# @prob: data-structure problem name,also the source file name

DS_BASE=./data-structures/${cate}
DS_OUT=${DS_BASE}/out

ds:
	g++ -std=c++11 -o ${DS_OUT}/${prob}.o ${DS_BASE}/${prob}.cpp

exec_ds:
	${DS_OUT}/${prob}.o

clean_ds:
	rm -rf ${DS_OUT}/${prob}.o ${DS_OUT}/${prob}.out

