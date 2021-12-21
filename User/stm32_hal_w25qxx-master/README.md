# STM32基于HAL库实现W25Qxx的读写

参考：`https://github.com/nimaltd/w25qxx.git`

- W25qxx使用spi，支持Mode0/Mode3(即CPOL=0/CPHA=0和CPOL=1/CPHA=1)

- 在 `w25qxx.h` 文件中更改spi和cs端口

- 写入数据前先做擦除操作

- W25QXX 由每页 256 字节组成，容量为 (XX/8)M 字节。
- 每页的 256 字节用一次页编程指令即可完成
- 每次可以擦除 16 页（1 个扇区，最小擦除单位）、 128 页（32KB 块）、 256 页（64KB 块）和全片擦除，存储数据地址为24位

- 使用`_W25QXX_DEBUG`就必须属于HAL库，因为涉及到`HAL_GetTick()`函数，除非删除`HAL_GetTick()`函数

> 例
> ```C
>  uint8_t write_data[100];
>  uint8_t read_data[100];
>  // memset(write_data, 0xAA, 100);
>  for (size_t i = 0; i < 100; i++)
>  {
>    write_data[i] = i;
>  }
>  W25qxx_Init();
>  W25qxx_EraseSector(0x00); //扇区擦除
>  W25qxx_WriteSector(write_data, 0x00, 0x00, 100); //扇区写入
>  // W25qxx_WritePage(write_data, 0x00, 0, 100); //页写入
>  W25qxx_ReadBytes(read_data, 0x00, 100); //多字节读取
>  // W25qxx_ReadPage(read_data, 0x00, 0, 100); //页读取
>  printf("\r\nwrite---------\r\n");
>  for (size_t i = 0; i < 100; i++)
>  {
>    printf("0x%02x ", write_data[i]);
>  }
>  printf("\r\nread----------\r\n");
>  for (size_t i = 0; i < 100; i++)
>  {
>    printf("0x%02X ", read_data[i]);
>  }
>  if (memcpy(write_data, read_data, 100))
>    printf("\r\nSUCCESS\r\n");
>  else
>    printf("\r\nERROR\r\n");
> ```
