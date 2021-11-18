# cli args: 
# @cate: algorithm category
# @prob: algorithm problem name,also the source file name

BASE=./algorithms/${cate}
OUT=${BASE}/out

algo:
	g++ -o ${OUT}/${prob}.o ${BASE}/${prob}.cpp

exec:
	${OUT}/${prob}.o

clean_algo:
	rm -rf ${OUT}/${prob}.o ${OUT}/${prob}.out

