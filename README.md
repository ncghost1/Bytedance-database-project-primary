# 【字学镜像计划 后端&大数据-初级】内存数据布局
实现了RowTable和ColumnTable的GetIntField()和PutIntField()以及ColumnSun()方法。<br>
**注：运行sh configure.sh命令安装google test framework，若已安装先运行sh build.sh --clean --lab1命令后运行cd build && ctest -VV -R "database_*" -j进行lab1 test。**<br>
This is a project based on stanford cs245.<br>
(2022.2.9 该项目已通过字学镜像计划验收！）
# Prerequisite
- cmake version(recommended): >=3.9.2
- C++ version: >=C++11
- gcc/g++ version: >=6.3.0

# Step 1
Configure googletest framework in your environment.

`sh configure.sh`

After configuration, binary files of google test will be installed in your environment.

# Step 2
Implement your database in C++, then build binary outputs (executables for unit test).

If you are working with lab1, you can build unit tests only for lab1,

`sh build.sh --clean --lab1`

or for lab2,

`sh build.sh --clean --lab2`

or for both labs

`sh build.sh --clean --lab1 --lab2`

# Step 3
Enter the test directory, run all unit tests.

`cd build && ctest -VV -R "database_*" -j`
