#ifndef __SPARK_FILE_H__
#define __SPARK_FILE_H__

class File{
public:
	File(const char* filename);
	virtual ~File();

	int GetSize() const;
	const char* GetData() const;
	unsigned GetUnsignedInt(int position) const;	
	static void Write(const char* filename, const char* data, int size);

private:
	int m_Size;             // file size
	char* m_Data;          
};

#endif
