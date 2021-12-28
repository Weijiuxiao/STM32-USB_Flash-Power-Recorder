
#include "w25qxx.h"

#if (_W25QXX_DEBUG == 1)
#include <stdio.h>
#endif

#if (_W25QXX_USE_FREERTOS == 1)
#include "cmsis_os.h"
#define W25qxx_Delay(delay) osDelay(delay)
#else
#define W25qxx_Delay(delay) HAL_Delay(delay)
#endif

w25qxx_t w25qxx;

/**
 * @function: uint8_t W25qxx_Spi(uint8_t Data)
 * @description: W25qxx的spi字节读写
 * @param {uint8_t} Data待写入的数据
 * @return {ret} 读取的数据
 */
uint8_t W25qxx_Spi(uint8_t Data)
{
  uint8_t ret;
  HAL_SPI_TransmitReceive(&_W25QXX_SPI, &Data, &ret, 1, 100);
  return ret;
}

/**
 * @function: void W25qxx_Receive(uint8_t *Data, uint16_t DataSize)
 * @description:  W25qxx的spi读取多个字节
 * @param {uint8_t} *Data 待读取的数据
 * @param {uint16_t} DataSize 待读取数据的大小
 * @return {*}
 */
void W25qxx_Receive(uint8_t *Data, uint16_t DataSize)
{
  HAL_SPI_Receive(&_W25QXX_SPI, Data, DataSize, 2000);
}

/**
 * @function: void W25qxx_Transmit(uint8_t *Data, uint16_t DataSize)
 * @description:  W25qxx的spi写入多个字节
 * @param {uint8_t} *Data 待写入的数据
 * @param {uint16_t} DataSize 待写入数据的大小
 * @return {*}
 */
void W25qxx_Transmit(uint8_t *Data, uint16_t DataSize)
{
  HAL_SPI_Transmit(&_W25QXX_SPI, Data, DataSize, 100);
}

/**
 * @function: uint32_t W25qxx_ReadID(void)
 * @description: W25qxx读取芯片ID
 * @param {*}
 * @return {Temp} 读取的ID
 */
uint32_t W25qxx_ReadID(void)
{
  uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;
  _W25QXX_CS_(0);
  W25qxx_Spi(JEDEC_ID);
  Temp0 = W25qxx_Spi(W25QXX_DUMMY_BYTE);
  Temp1 = W25qxx_Spi(W25QXX_DUMMY_BYTE);
  Temp2 = W25qxx_Spi(W25QXX_DUMMY_BYTE);
  _W25QXX_CS_(1);
  Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
  return Temp;
}

/**
 * @function: void W25qxx_ReadUniqID(void)
 * @description: 读取唯一ID
 * @param {*}
 * @return {*}
 */
void W25qxx_ReadUniqID(void)
{
  _W25QXX_CS_(0);
  W25qxx_Spi(UNIQUE_ID);
  for (uint8_t i = 0; i < 4; i++)
    W25qxx_Spi(W25QXX_DUMMY_BYTE);
  for (uint8_t i = 0; i < 8; i++)
    w25qxx.UniqID[i] = W25qxx_Spi(W25QXX_DUMMY_BYTE);
  _W25QXX_CS_(1);
}

/**
 * @function: void W25qxx_WriteEnable(void)
 * @description: 使能写入
 * @param {*}
 * @return {*}
 */
void W25qxx_WriteEnable(void)
{
  _W25QXX_CS_(0);
  W25qxx_Spi(WRITE_ENABLE);
  _W25QXX_CS_(1);
  W25qxx_Delay(1);
}

/**
 * @function: void W25qxx_WriteDisable(void)
 * @description: 失能写入
 * @param {*}
 * @return {*}
 */
void W25qxx_WriteDisable(void)
{
  _W25QXX_CS_(0);
  W25qxx_Spi(WRITE_DISABLE);
  _W25QXX_CS_(1);
  W25qxx_Delay(1);
}

/**
 * @function: uint8_t W25qxx_ReadStatusRegister(uint8_t SelectStatusRegister_1_2_3)
 * @description: 获取读状态寄存器
 * @param {uint8_t} SelectStatusRegister_1_2_3 待获取的读状态寄存器1/2/3
 * @return {status} 读状态寄存器数据
 */
uint8_t W25qxx_ReadStatusRegister(uint8_t SelectStatusRegister_1_2_3)
{
  uint8_t status = 0;
  _W25QXX_CS_(0);
  if (SelectStatusRegister_1_2_3 == 1)
  {
    W25qxx_Spi(READ_STATUS_REGISTER_1);
    status = W25qxx_Spi(W25QXX_DUMMY_BYTE);
    w25qxx.StatusRegister1 = status;
  }
  else if (SelectStatusRegister_1_2_3 == 2)
  {
    W25qxx_Spi(READ_STATUS_REGISTER_2);
    status = W25qxx_Spi(W25QXX_DUMMY_BYTE);
    w25qxx.StatusRegister2 = status;
  }
  else
  {
    W25qxx_Spi(READ_STATUS_REGISTER_3);
    status = W25qxx_Spi(W25QXX_DUMMY_BYTE);
    w25qxx.StatusRegister3 = status;
  }
  _W25QXX_CS_(1);
  return status;
}

/**
 * @function: void W25qxx_WriteStatusRegister(uint8_t SelectStatusRegister_1_2_3, uint8_t Data)
 * @description: 获取写状态寄存器数据
 * @param {uint8_t} SelectStatusRegister_1_2_3 待获取的写状态寄存器1/2/3
 * @param {uint8_t} Data 状态寄存器数据
 * @return {*}
 */
void W25qxx_WriteStatusRegister(uint8_t SelectStatusRegister_1_2_3, uint8_t Data)
{
  _W25QXX_CS_(0);
  if (SelectStatusRegister_1_2_3 == 1)
  {
    W25qxx_Spi(WRITE_STATUS_REGISTER_1);
    w25qxx.StatusRegister1 = Data;
  }
  else if (SelectStatusRegister_1_2_3 == 2)
  {
    W25qxx_Spi(WRITE_STATUS_REGISTER_2);
    w25qxx.StatusRegister2 = Data;
  }
  else
  {
    W25qxx_Spi(WRITE_STATUS_REGISTER_3);
    w25qxx.StatusRegister3 = Data;
  }
  W25qxx_Spi(Data);
  _W25QXX_CS_(1);
}

/**
 * @function: void W25qxx_WaitForWriteEnd(void)
 * @description: 等待写入完成
 * @param {*}
 * @return {*}
 */
void W25qxx_WaitForWriteEnd(void)
{
  W25qxx_Delay(1);
  _W25QXX_CS_(0);
  W25qxx_Spi(READ_STATUS_REGISTER_1);
  do
  {
    w25qxx.StatusRegister1 = W25qxx_Spi(W25QXX_DUMMY_BYTE);
    W25qxx_Delay(1);
  } while ((w25qxx.StatusRegister1 & 0x01) == 0x01);
  _W25QXX_CS_(1);
}

/**
 * @function: bool W25qxx_Init(void)
 * @description: W25qxx初始化
 * @param {*}
 * @return {false} 初始化失败
 * @return {true} 初始化成功
 */
bool W25qxx_Init(void)
{
  w25qxx.Lock = 1;
  while (HAL_GetTick() < 100) //启动100m后才开始初始化
    W25qxx_Delay(1);
  _W25QXX_CS_(1);
  W25qxx_Delay(100);
  uint32_t id;
#if (_W25QXX_DEBUG == 1)
  printf("w25qxx Init Begin...\r\n");
#endif
  id = W25qxx_ReadID();

#if (_W25QXX_DEBUG == 1)
  printf("w25qxx ID:0x%lX\r\n", id);
#endif
  switch (id & 0x0000FFFF)
  {
  case 0x401A: //w25q512
    w25qxx.ID = W25Q512;
    w25qxx.BlockCount = 1024;
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx Chip: w25q512\r\n");
#endif
    break;
  case 0x4019: //w25q256
    w25qxx.ID = W25Q256;
    w25qxx.BlockCount = 512;
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx Chip: w25q256\r\n");
#endif
    break;
  case 0x4018: //w25q128
    w25qxx.ID = W25Q128;
    w25qxx.BlockCount = 256;
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx Chip: w25q128\r\n");
#endif
    break;
  case 0x4017: //w25q64
    w25qxx.ID = W25Q64;
    w25qxx.BlockCount = 128;
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx Chip: w25q64\r\n");
#endif
    break;
  case 0x4016: //w25q32
    w25qxx.ID = W25Q32;
    w25qxx.BlockCount = 64;
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx Chip: w25q32\r\n");
#endif
    break;
  case 0x4015: //w25q16
    w25qxx.ID = W25Q16;
    w25qxx.BlockCount = 32;
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx Chip: w25q16\r\n");
#endif
    break;
  case 0x4014: //w25q80
    w25qxx.ID = W25Q80;
    w25qxx.BlockCount = 16;
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx Chip: w25q80\r\n");
#endif
    break;
  case 0x4013: //w25q40
    w25qxx.ID = W25Q40;
    w25qxx.BlockCount = 8;
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx Chip: w25q40\r\n");
#endif
    break;
  case 0x4012: //w25q20
    w25qxx.ID = W25Q20;
    w25qxx.BlockCount = 4;
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx Chip: w25q20\r\n");
#endif
    break;
  case 0x4011: //w25q10
    w25qxx.ID = W25Q10;
    w25qxx.BlockCount = 2;
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx Chip: w25q10\r\n");
#endif
    break;
  default:
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx Unknown ID\r\n");
#endif
    w25qxx.Lock = 0;
    return false;
  }
  w25qxx.PageSize = 256;
  w25qxx.SectorSize = 0x1000;
  w25qxx.SectorCount = w25qxx.BlockCount * 16;
  w25qxx.PageCount = (w25qxx.SectorCount * w25qxx.SectorSize) / w25qxx.PageSize;
  w25qxx.BlockSize = w25qxx.SectorSize * 16;
  w25qxx.CapacityInKiloByte = (w25qxx.SectorCount * w25qxx.SectorSize) / 1024;
  W25qxx_ReadUniqID();
  W25qxx_ReadStatusRegister(1);
  W25qxx_ReadStatusRegister(2);
  W25qxx_ReadStatusRegister(3);
#if (_W25QXX_DEBUG == 1)
  printf("w25qxx Page Size: %d Bytes\r\n", w25qxx.PageSize);
  printf("w25qxx Page Count: %ld\r\n", w25qxx.PageCount);
  printf("w25qxx Sector Size: %ld Bytes\r\n", w25qxx.SectorSize);
  printf("w25qxx Sector Count: %ld\r\n", w25qxx.SectorCount);
  printf("w25qxx Block Size: %ld Bytes\r\n", w25qxx.BlockSize);
  printf("w25qxx Block Count: %ld\r\n", w25qxx.BlockCount);
  printf("w25qxx Capacity: %ld KiloBytes\r\n", w25qxx.CapacityInKiloByte);
  printf("w25qxx Init Done\r\n");
#endif
  w25qxx.Lock = 0;
  return true;
}

/**
 * @function: void W25qxx_EraseChip(void)
 * @description: W25qxx擦除芯片
 * @param {*}
 * @return {*}
 */
void W25qxx_EraseChip(void)
{
  while (w25qxx.Lock == 1)
    W25qxx_Delay(1);
  w25qxx.Lock = 1;
#if (_W25QXX_DEBUG == 1)
  uint32_t StartTime = HAL_GetTick();
  printf("w25qxx EraseChip Begin...\r\n");
#endif
  W25qxx_WriteEnable();
  _W25QXX_CS_(0);
  W25qxx_Spi(CHIP_ERASE);
  _W25QXX_CS_(1);
  W25qxx_WaitForWriteEnd();
#if (_W25QXX_DEBUG == 1)
  printf("w25qxx EraseBlock done after %ld ms!\r\n", HAL_GetTick() - StartTime);
#endif
  W25qxx_Delay(10);
  w25qxx.Lock = 0;
}

/**
 * @function: void W25qxx_EraseSector(uint32_t SectorAddr)
 * @description: 擦除扇区
 * @param {uint32_t} SectorAddr 待擦除的扇区地址
 * @return {*}
 */
void W25qxx_EraseSector(uint32_t SectorAddr)
{
  while (w25qxx.Lock == 1)
    W25qxx_Delay(1);
  w25qxx.Lock = 1;
#if (_W25QXX_DEBUG == 1)
  uint32_t StartTime = HAL_GetTick();
  printf("w25qxx EraseSector %ld Begin...\r\n", SectorAddr);
#endif
  W25qxx_WaitForWriteEnd();
  SectorAddr = SectorAddr * w25qxx.SectorSize;
  W25qxx_WriteEnable();
  _W25QXX_CS_(0);
  W25qxx_Spi(SECTOR_ERASE);
  if (w25qxx.ID >= W25Q256)
    W25qxx_Spi((SectorAddr & 0xFF000000) >> 24);
  W25qxx_Spi((SectorAddr & 0xFF0000) >> 16);
  W25qxx_Spi((SectorAddr & 0xFF00) >> 8);
  W25qxx_Spi(SectorAddr & 0xFF);
  _W25QXX_CS_(1);
  W25qxx_WaitForWriteEnd();
#if (_W25QXX_DEBUG == 1)
  printf("w25qxx EraseSector done after %ld ms\r\n", HAL_GetTick() - StartTime);
#endif
  W25qxx_Delay(1);
  w25qxx.Lock = 0;
}

/**
 * @function: void W25qxx_EraseBlock(uint32_t BlockAddr)
 * @description: 擦除块
 * @param {uint32_t} BlockAddr 待擦除的块地址
 * @return {*}
 */
void W25qxx_EraseBlock(uint32_t BlockAddr)
{
  while (w25qxx.Lock == 1)
    W25qxx_Delay(1);
  w25qxx.Lock = 1;
#if (_W25QXX_DEBUG == 1)
  printf("w25qxx EraseBlock %ld Begin...\r\n", BlockAddr);
  W25qxx_Delay(100);
  uint32_t StartTime = HAL_GetTick();
#endif
  W25qxx_WaitForWriteEnd();
  BlockAddr = BlockAddr * w25qxx.SectorSize * 16;
  W25qxx_WriteEnable();
  _W25QXX_CS_(0);
  W25qxx_Spi(BLOCK_ERASE);
  if (w25qxx.ID >= W25Q256)
    W25qxx_Spi((BlockAddr & 0xFF000000) >> 24);
  W25qxx_Spi((BlockAddr & 0xFF0000) >> 16);
  W25qxx_Spi((BlockAddr & 0xFF00) >> 8);
  W25qxx_Spi(BlockAddr & 0xFF);
  _W25QXX_CS_(1);
  W25qxx_WaitForWriteEnd();
#if (_W25QXX_DEBUG == 1)
  printf("w25qxx EraseBlock done after %ld ms\r\n", HAL_GetTick() - StartTime);
  W25qxx_Delay(100);
#endif
  W25qxx_Delay(1);
  w25qxx.Lock = 0;
}

/**
 * @function: uint32_t W25qxx_PageToSector(uint32_t PageAddress)
 * @description: 
 * @param {uint32_t} PageAddress
 * @return {*}
 */
uint32_t W25qxx_PageToSector(uint32_t PageAddress)
{
  return ((PageAddress * w25qxx.PageSize) / w25qxx.SectorSize);
}

/**
 * @function: uint32_t W25qxx_PageToBlock(uint32_t PageAddress)
 * @description: 
 * @param {*}
 * @return {*}
 */
uint32_t W25qxx_PageToBlock(uint32_t PageAddress)
{
  return ((PageAddress * w25qxx.PageSize) / w25qxx.BlockSize);
}

/**
 * @function: uint32_t W25qxx_SectorToBlock(uint32_t SectorAddress)
 * @description: 
 * @param {uint32_t} SectorAddress
 * @return {*}
 */
uint32_t W25qxx_SectorToBlock(uint32_t SectorAddress)
{
  return ((SectorAddress * w25qxx.SectorSize) / w25qxx.BlockSize);
}

/**
 * @function: uint32_t W25qxx_SectorToPage(uint32_t SectorAddress)
 * @description: 
 * @param {uint32_t} SectorAddress
 * @return {*}
 */
uint32_t W25qxx_SectorToPage(uint32_t SectorAddress)
{
  return (SectorAddress * w25qxx.SectorSize) / w25qxx.PageSize;
}

/**
 * @function: uint32_t W25qxx_BlockToPage(uint32_t BlockAddress)
 * @description: 
 * @param {uint32_t} BlockAddress
 * @return {*}
 */
uint32_t W25qxx_BlockToPage(uint32_t BlockAddress)
{
  return (BlockAddress * w25qxx.BlockSize) / w25qxx.PageSize;
}

/**
 * @function: bool W25qxx_IsEmptyPage(uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_PageSize)
 * @description: 页是否为空
 * @param {uint32_t} Page_Address
 * @param {uint32_t} OffsetInByte
 * @param {uint32_t} NumByteToCheck_up_to_PageSize
 * @return {false} 不为空
 * @return {true} 为空
 */
bool W25qxx_IsEmptyPage(uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_PageSize)
{
  while (w25qxx.Lock == 1)
    W25qxx_Delay(1);
  w25qxx.Lock = 1;
  if (((NumByteToCheck_up_to_PageSize + OffsetInByte) > w25qxx.PageSize) || (NumByteToCheck_up_to_PageSize == 0))
    NumByteToCheck_up_to_PageSize = w25qxx.PageSize - OffsetInByte;
#if (_W25QXX_DEBUG == 1)
  printf("w25qxx CheckPage:%ld, Offset:%ld, Bytes:%ld begin...\r\n", Page_Address, OffsetInByte, NumByteToCheck_up_to_PageSize);
  W25qxx_Delay(100);
  uint32_t StartTime = HAL_GetTick();
#endif
  uint8_t pBuffer[32];
  uint32_t WorkAddress;
  uint32_t i;
  for (i = OffsetInByte; i < w25qxx.PageSize; i += sizeof(pBuffer))
  {
    _W25QXX_CS_(0);
    WorkAddress = (i + Page_Address * w25qxx.PageSize);
    W25qxx_Spi(FAST_READ);
    if (w25qxx.ID >= W25Q256)
      W25qxx_Spi((WorkAddress & 0xFF000000) >> 24);
    W25qxx_Spi((WorkAddress & 0xFF0000) >> 16);
    W25qxx_Spi((WorkAddress & 0xFF00) >> 8);
    W25qxx_Spi(WorkAddress & 0xFF);
    W25qxx_Spi(0);
    W25qxx_Receive(pBuffer, sizeof(pBuffer));
    _W25QXX_CS_(1);
    for (uint8_t x = 0; x < sizeof(pBuffer); x++)
    {
      if (pBuffer[x] != 0xFF)
        goto NOT_EMPTY;
    }
  }
  if ((w25qxx.PageSize + OffsetInByte) % sizeof(pBuffer) != 0)
  {
    i -= sizeof(pBuffer);
    for (; i < w25qxx.PageSize; i++)
    {
      _W25QXX_CS_(0);
      WorkAddress = (i + Page_Address * w25qxx.PageSize);
      W25qxx_Spi(FAST_READ);
      if (w25qxx.ID >= W25Q256)
        W25qxx_Spi((WorkAddress & 0xFF000000) >> 24);
      W25qxx_Spi((WorkAddress & 0xFF0000) >> 16);
      W25qxx_Spi((WorkAddress & 0xFF00) >> 8);
      W25qxx_Spi(WorkAddress & 0xFF);
      W25qxx_Spi(0);
      W25qxx_Receive(pBuffer, 1);
      _W25QXX_CS_(1);
      if (pBuffer[0] != 0xFF)
        goto NOT_EMPTY;
    }
  }
#if (_W25QXX_DEBUG == 1)
  printf("w25qxx CheckPage is Empty in %ld ms\r\n", HAL_GetTick() - StartTime);
  W25qxx_Delay(100);
#endif
  w25qxx.Lock = 0;
  return true;
NOT_EMPTY:
#if (_W25QXX_DEBUG == 1)
  printf("w25qxx CheckPage is Not Empty in %ld ms\r\n", HAL_GetTick() - StartTime);
  W25qxx_Delay(100);
#endif
  w25qxx.Lock = 0;
  return false;
}

/**
 * @function: bool W25qxx_IsEmptySector(uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_SectorSize)
 * @description: 扇区是否为空
 * @param {uint32_t} Sector_Address
 * @param {uint32_t} OffsetInByte
 * @param {uint32_t} NumByteToCheck_up_to_SectorSize
 * @return {false} 不为空
 * @return {true} 为空
 */
bool W25qxx_IsEmptySector(uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_SectorSize)
{
  while (w25qxx.Lock == 1)
    W25qxx_Delay(1);
  w25qxx.Lock = 1;
  if ((NumByteToCheck_up_to_SectorSize > w25qxx.SectorSize) || (NumByteToCheck_up_to_SectorSize == 0))
    NumByteToCheck_up_to_SectorSize = w25qxx.SectorSize;
#if (_W25QXX_DEBUG == 1)
  printf("w25qxx CheckSector:%ld, Offset:%ld, Bytes:%ld begin...\r\n", Sector_Address, OffsetInByte, NumByteToCheck_up_to_SectorSize);
  W25qxx_Delay(100);
  uint32_t StartTime = HAL_GetTick();
#endif
  uint8_t pBuffer[32];
  uint32_t WorkAddress;
  uint32_t i;
  for (i = OffsetInByte; i < w25qxx.SectorSize; i += sizeof(pBuffer))
  {
    _W25QXX_CS_(0);
    WorkAddress = (i + Sector_Address * w25qxx.SectorSize);
    W25qxx_Spi(FAST_READ);
    if (w25qxx.ID >= W25Q256)
      W25qxx_Spi((WorkAddress & 0xFF000000) >> 24);
    W25qxx_Spi((WorkAddress & 0xFF0000) >> 16);
    W25qxx_Spi((WorkAddress & 0xFF00) >> 8);
    W25qxx_Spi(WorkAddress & 0xFF);
    W25qxx_Spi(0);
    W25qxx_Receive(pBuffer, sizeof(pBuffer));
    _W25QXX_CS_(1);
    for (uint8_t x = 0; x < sizeof(pBuffer); x++)
    {
      if (pBuffer[x] != 0xFF)
        goto NOT_EMPTY;
    }
  }
  if ((w25qxx.SectorSize + OffsetInByte) % sizeof(pBuffer) != 0)
  {
    i -= sizeof(pBuffer);
    for (; i < w25qxx.SectorSize; i++)
    {
      _W25QXX_CS_(0);
      WorkAddress = (i + Sector_Address * w25qxx.SectorSize);
      W25qxx_Spi(FAST_READ);
      if (w25qxx.ID >= W25Q256)
        W25qxx_Spi((WorkAddress & 0xFF000000) >> 24);
      W25qxx_Spi((WorkAddress & 0xFF0000) >> 16);
      W25qxx_Spi((WorkAddress & 0xFF00) >> 8);
      W25qxx_Spi(WorkAddress & 0xFF);
      W25qxx_Spi(0);
      W25qxx_Receive(pBuffer, 1);
      _W25QXX_CS_(1);
      if (pBuffer[0] != 0xFF)
        goto NOT_EMPTY;
    }
  }
#if (_W25QXX_DEBUG == 1)
  printf("w25qxx CheckSector is Empty in %ld ms\r\n", HAL_GetTick() - StartTime);
  W25qxx_Delay(100);
#endif
  w25qxx.Lock = 0;
  return true;
NOT_EMPTY:
#if (_W25QXX_DEBUG == 1)
  printf("w25qxx CheckSector is Not Empty in %ld ms\r\n", HAL_GetTick() - StartTime);
  W25qxx_Delay(100);
#endif
  w25qxx.Lock = 0;
  return false;
}

/**
 * @function: bool W25qxx_IsEmptyBlock(uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_BlockSize)
 * @description: 
 * @param {uint32_t} Block_Address
 * @param {uint32_t} OffsetInByte
 * @param {uint32_t} NumByteToCheck_up_to_BlockSize
 * @return {false} 不为空
 * @return {true} 为空
 */
bool W25qxx_IsEmptyBlock(uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_BlockSize)
{
  while (w25qxx.Lock == 1)
    W25qxx_Delay(1);
  w25qxx.Lock = 1;
  if ((NumByteToCheck_up_to_BlockSize > w25qxx.BlockSize) || (NumByteToCheck_up_to_BlockSize == 0))
    NumByteToCheck_up_to_BlockSize = w25qxx.BlockSize;
#if (_W25QXX_DEBUG == 1)
  printf("w25qxx CheckBlock:%ld, Offset:%ld, Bytes:%ld begin...\r\n", Block_Address, OffsetInByte, NumByteToCheck_up_to_BlockSize);
  W25qxx_Delay(100);
  uint32_t StartTime = HAL_GetTick();
#endif
  uint8_t pBuffer[32];
  uint32_t WorkAddress;
  uint32_t i;
  for (i = OffsetInByte; i < w25qxx.BlockSize; i += sizeof(pBuffer))
  {
    _W25QXX_CS_(0);
    WorkAddress = (i + Block_Address * w25qxx.BlockSize);
    W25qxx_Spi(FAST_READ);
    if (w25qxx.ID >= W25Q256)
      W25qxx_Spi((WorkAddress & 0xFF000000) >> 24);
    W25qxx_Spi((WorkAddress & 0xFF0000) >> 16);
    W25qxx_Spi((WorkAddress & 0xFF00) >> 8);
    W25qxx_Spi(WorkAddress & 0xFF);
    W25qxx_Spi(0);
    W25qxx_Receive(pBuffer, sizeof(pBuffer));
    _W25QXX_CS_(1);
    for (uint8_t x = 0; x < sizeof(pBuffer); x++)
    {
      if (pBuffer[x] != 0xFF)
        goto NOT_EMPTY;
    }
  }
  if ((w25qxx.BlockSize + OffsetInByte) % sizeof(pBuffer) != 0)
  {
    i -= sizeof(pBuffer);
    for (; i < w25qxx.BlockSize; i++)
    {
      _W25QXX_CS_(0);
      WorkAddress = (i + Block_Address * w25qxx.BlockSize);
      W25qxx_Spi(FAST_READ);
      if (w25qxx.ID >= W25Q256)
        W25qxx_Spi((WorkAddress & 0xFF000000) >> 24);
      W25qxx_Spi((WorkAddress & 0xFF0000) >> 16);
      W25qxx_Spi((WorkAddress & 0xFF00) >> 8);
      W25qxx_Spi(WorkAddress & 0xFF);
      W25qxx_Spi(0);
      W25qxx_Receive(pBuffer, 1);
      _W25QXX_CS_(1);
      if (pBuffer[0] != 0xFF)
        goto NOT_EMPTY;
    }
  }
#if (_W25QXX_DEBUG == 1)
  printf("w25qxx CheckBlock is Empty in %ld ms\r\n", HAL_GetTick() - StartTime);
  W25qxx_Delay(100);
#endif
  w25qxx.Lock = 0;
  return true;
NOT_EMPTY:
#if (_W25QXX_DEBUG == 1)
  printf("w25qxx CheckBlock is Not Empty in %ld ms\r\n", HAL_GetTick() - StartTime);
  W25qxx_Delay(100);
#endif
  w25qxx.Lock = 0;
  return false;
}

/**
 * @function: void W25qxx_WriteByte(uint8_t pBuffer, uint32_t WriteAddr_inBytes)
 * @description: 字节写入
 * @param {uint8_t} pBuffer 待写入的数据
 * @param {uint32_t} WriteAddr_inBytes 待写入的字节地址
 * @return {*}
 */
void W25qxx_WriteByte(uint8_t pBuffer, uint32_t WriteAddr_inBytes)
{
  while (w25qxx.Lock == 1)
    W25qxx_Delay(1);
  w25qxx.Lock = 1;
#if (_W25QXX_DEBUG == 1)
  uint32_t StartTime = HAL_GetTick();
  printf("w25qxx WriteByte 0x%02X at address %ld begin...", pBuffer, WriteAddr_inBytes);
#endif
  W25qxx_WaitForWriteEnd();
  W25qxx_WriteEnable();
  _W25QXX_CS_(0);
  W25qxx_Spi(PAGE_PROGRAM);
  if (w25qxx.ID >= W25Q256)
    W25qxx_Spi((WriteAddr_inBytes & 0xFF000000) >> 24);
  W25qxx_Spi((WriteAddr_inBytes & 0xFF0000) >> 16);
  W25qxx_Spi((WriteAddr_inBytes & 0xFF00) >> 8);
  W25qxx_Spi(WriteAddr_inBytes & 0xFF);
  W25qxx_Spi(pBuffer);
  _W25QXX_CS_(1);
  W25qxx_WaitForWriteEnd();
#if (_W25QXX_DEBUG == 1)
  printf("w25qxx WriteByte done after %ld ms\r\n", HAL_GetTick() - StartTime);
#endif
  w25qxx.Lock = 0;
}

/**
 * @function: void W25qxx_WritePage(uint8_t *pBuffer, uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_PageSize)
 * @description: 页写入
 * @param {uint8_t} *pBuffer 待写入的数据
 * @param {uint32_t} Page_Address 待写入的页地址
 * @param {uint32_t} OffsetInByte
 * @param {uint32_t} NumByteToWrite_up_to_PageSize
 * @return {*}
 */
void W25qxx_WritePage(uint8_t *pBuffer, uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_PageSize)
{
  while (w25qxx.Lock == 1)
    W25qxx_Delay(1);
  w25qxx.Lock = 1;
  if (((NumByteToWrite_up_to_PageSize + OffsetInByte) > w25qxx.PageSize) || (NumByteToWrite_up_to_PageSize == 0))
    NumByteToWrite_up_to_PageSize = w25qxx.PageSize - OffsetInByte;
  if ((OffsetInByte + NumByteToWrite_up_to_PageSize) > w25qxx.PageSize)
    NumByteToWrite_up_to_PageSize = w25qxx.PageSize - OffsetInByte;
#if (_W25QXX_DEBUG == 1)
  printf("w25qxx WritePage:%ld, Offset:%ld ,Writes %ld Bytes, begin...\r\n", Page_Address, OffsetInByte, NumByteToWrite_up_to_PageSize);
  W25qxx_Delay(100);
  uint32_t StartTime = HAL_GetTick();
#endif
  W25qxx_WaitForWriteEnd();
  W25qxx_WriteEnable();
  _W25QXX_CS_(0);
  W25qxx_Spi(PAGE_PROGRAM);
  Page_Address = (Page_Address * w25qxx.PageSize) + OffsetInByte;
  if (w25qxx.ID >= W25Q256)
    W25qxx_Spi((Page_Address & 0xFF000000) >> 24);
  W25qxx_Spi((Page_Address & 0xFF0000) >> 16);
  W25qxx_Spi((Page_Address & 0xFF00) >> 8);
  W25qxx_Spi(Page_Address & 0xFF);
  W25qxx_Transmit(pBuffer, NumByteToWrite_up_to_PageSize);
  _W25QXX_CS_(1);
  W25qxx_WaitForWriteEnd();
#if (_W25QXX_DEBUG == 1)
  StartTime = HAL_GetTick() - StartTime;
  for (uint32_t i = 0; i < NumByteToWrite_up_to_PageSize; i++)
  {
    if ((i % 8 == 0) && (i > 2))
    {
      printf("\r\n");
      W25qxx_Delay(10);
    }
    printf("0x%02X,", pBuffer[i]);
  }
  printf("\r\n");
  printf("w25qxx WritePage done after %ld ms\r\n", StartTime);
  W25qxx_Delay(100);
#endif
  W25qxx_Delay(1);
  w25qxx.Lock = 0;
}

/**
 * @function: void W25qxx_WriteSector(uint8_t *pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_SectorSize)
 * @description: 扇区写入
 * @param {uint8_t} *pBuffer 待写入的数据
 * @param {uint32_t} Sector_Address 待写入的扇区地址
 * @param {uint32_t} OffsetInByte
 * @param {uint32_t} NumByteToWrite_up_to_SectorSize
 * @return {*}
 */
void W25qxx_WriteSector(uint8_t *pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_SectorSize)
{
  if ((NumByteToWrite_up_to_SectorSize > w25qxx.SectorSize) || (NumByteToWrite_up_to_SectorSize == 0))
    NumByteToWrite_up_to_SectorSize = w25qxx.SectorSize;
#if (_W25QXX_DEBUG == 1)
  printf("+++w25qxx WriteSector:%ld, Offset:%ld ,Write %ld Bytes, begin...\r\n", Sector_Address, OffsetInByte, NumByteToWrite_up_to_SectorSize);
  W25qxx_Delay(100);
#endif
  if (OffsetInByte >= w25qxx.SectorSize)
  {
#if (_W25QXX_DEBUG == 1)
    printf("---w25qxx WriteSector Faild!\r\n");
    W25qxx_Delay(100);
#endif
    return;
  }
  uint32_t StartPage;
  int32_t BytesToWrite;
  uint32_t LocalOffset;
  if ((OffsetInByte + NumByteToWrite_up_to_SectorSize) > w25qxx.SectorSize)
    BytesToWrite = w25qxx.SectorSize - OffsetInByte;
  else
    BytesToWrite = NumByteToWrite_up_to_SectorSize;
  StartPage = W25qxx_SectorToPage(Sector_Address) + (OffsetInByte / w25qxx.PageSize);
  LocalOffset = OffsetInByte % w25qxx.PageSize;
  do
  {
    W25qxx_WritePage(pBuffer, StartPage, LocalOffset, BytesToWrite);
    StartPage++;
    BytesToWrite -= w25qxx.PageSize - LocalOffset;
    pBuffer += w25qxx.PageSize - LocalOffset;
    LocalOffset = 0;
  } while (BytesToWrite > 0);
#if (_W25QXX_DEBUG == 1)
  printf("---w25qxx WriteSector Done\r\n");
  W25qxx_Delay(100);
#endif
}

/**
 * @function: void W25qxx_WriteBlock(uint8_t *pBuffer, uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_BlockSize)
 * @description: 块写入
 * @param {uint8_t} *pBuffer 待写入数据
 * @param {uint32_t} Block_Address 待写入块地址
 * @param {uint32_t} OffsetInByte
 * @param {uint32_t} NumByteToWrite_up_to_BlockSize
 * @return {*}
 */
void W25qxx_WriteBlock(uint8_t *pBuffer, uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_BlockSize)
{
  if ((NumByteToWrite_up_to_BlockSize > w25qxx.BlockSize) || (NumByteToWrite_up_to_BlockSize == 0))
    NumByteToWrite_up_to_BlockSize = w25qxx.BlockSize;
#if (_W25QXX_DEBUG == 1)
  printf("+++w25qxx WriteBlock:%ld, Offset:%ld ,Write %ld Bytes, begin...\r\n", Block_Address, OffsetInByte, NumByteToWrite_up_to_BlockSize);
  W25qxx_Delay(100);
#endif
  if (OffsetInByte >= w25qxx.BlockSize)
  {
#if (_W25QXX_DEBUG == 1)
    printf("---w25qxx WriteBlock Faild!\r\n");
    W25qxx_Delay(100);
#endif
    return;
  }
  uint32_t StartPage;
  int32_t BytesToWrite;
  uint32_t LocalOffset;
  if ((OffsetInByte + NumByteToWrite_up_to_BlockSize) > w25qxx.BlockSize)
    BytesToWrite = w25qxx.BlockSize - OffsetInByte;
  else
    BytesToWrite = NumByteToWrite_up_to_BlockSize;
  StartPage = W25qxx_BlockToPage(Block_Address) + (OffsetInByte / w25qxx.PageSize);
  LocalOffset = OffsetInByte % w25qxx.PageSize;
  do
  {
    W25qxx_WritePage(pBuffer, StartPage, LocalOffset, BytesToWrite);
    StartPage++;
    BytesToWrite -= w25qxx.PageSize - LocalOffset;
    pBuffer += w25qxx.PageSize - LocalOffset;
    LocalOffset = 0;
  } while (BytesToWrite > 0);
#if (_W25QXX_DEBUG == 1)
  printf("---w25qxx WriteBlock Done\r\n");
  W25qxx_Delay(100);
#endif
}

/**
 * @function: void W25qxx_ReadByte(uint8_t *pBuffer, uint32_t Bytes_Address)
 * @description: 字节读取
 * @param {uint8_t} *pBuffer 读取的数据
 * @param {uint32_t} Bytes_Address 读取的字节地址
 * @return {*}
 */
void W25qxx_ReadByte(uint8_t *pBuffer, uint32_t Bytes_Address)
{
  while (w25qxx.Lock == 1)
    W25qxx_Delay(1);
  w25qxx.Lock = 1;
#if (_W25QXX_DEBUG == 1)
  uint32_t StartTime = HAL_GetTick();
  printf("w25qxx ReadByte at address %ld begin...\r\n", Bytes_Address);
#endif
  _W25QXX_CS_(0);
  W25qxx_Spi(FAST_READ);
  if (w25qxx.ID >= W25Q256)
    W25qxx_Spi((Bytes_Address & 0xFF000000) >> 24);
  W25qxx_Spi((Bytes_Address & 0xFF0000) >> 16);
  W25qxx_Spi((Bytes_Address & 0xFF00) >> 8);
  W25qxx_Spi(Bytes_Address & 0xFF);
  W25qxx_Spi(0);
  *pBuffer = W25qxx_Spi(W25QXX_DUMMY_BYTE);
  _W25QXX_CS_(1);
#if (_W25QXX_DEBUG == 1)
  printf("w25qxx ReadByte 0x%02X done after %ld ms\r\n", *pBuffer, HAL_GetTick() - StartTime);
#endif
  w25qxx.Lock = 0;
}

/**
 * @function: void W25qxx_ReadBytes(uint8_t *pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead)
 * @description: 多字节读取
 * @param {uint8_t} *pBuffer 待读取的数据
 * @param {uint32_t} ReadAddr 读取的地址
 * @param {uint32_t} NumByteToRead 读取数据的大小
 * @return {*}
 */
void W25qxx_ReadBytes(uint8_t *pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead)
{
  while (w25qxx.Lock == 1)
    W25qxx_Delay(1);
  w25qxx.Lock = 1;
#if (_W25QXX_DEBUG == 1)
  uint32_t StartTime = HAL_GetTick();
  printf("w25qxx ReadBytes at Address:%ld, %ld Bytes  begin...\r\n", ReadAddr, NumByteToRead);
#endif
  _W25QXX_CS_(0);
  W25qxx_Spi(FAST_READ);
  if (w25qxx.ID >= W25Q256)
    W25qxx_Spi((ReadAddr & 0xFF000000) >> 24);
  W25qxx_Spi((ReadAddr & 0xFF0000) >> 16);
  W25qxx_Spi((ReadAddr & 0xFF00) >> 8);
  W25qxx_Spi(ReadAddr & 0xFF);
  W25qxx_Spi(0);
  W25qxx_Receive(pBuffer, NumByteToRead);
  _W25QXX_CS_(1);
#if (_W25QXX_DEBUG == 1)
  StartTime = HAL_GetTick() - StartTime;
  for (uint32_t i = 0; i < NumByteToRead; i++)
  {
    if ((i % 8 == 0) && (i > 2))
    {
      printf("\r\n");
      W25qxx_Delay(10);
    }
    printf("0x%02X,", pBuffer[i]);
  }
  printf("\r\n");
  printf("w25qxx ReadBytes done after %ld ms\r\n", StartTime);
  W25qxx_Delay(100);
#endif
  W25qxx_Delay(1);
  w25qxx.Lock = 0;
}

/**
 * @function: void W25qxx_ReadPage(uint8_t *pBuffer, uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_PageSize)
 * @description: 页读取
 * @param {uint8_t} *pBuffer 读取的数据
 * @param {uint32_t} Page_Address 读取的页地址
 * @param {uint32_t} OffsetInByte
 * @param {uint32_t} NumByteToRead_up_to_PageSize
 * @return {*}
 */
void W25qxx_ReadPage(uint8_t *pBuffer, uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_PageSize)
{
  while (w25qxx.Lock == 1)
    W25qxx_Delay(1);
  w25qxx.Lock = 1;
  if ((NumByteToRead_up_to_PageSize > w25qxx.PageSize) || (NumByteToRead_up_to_PageSize == 0))
    NumByteToRead_up_to_PageSize = w25qxx.PageSize;
  if ((OffsetInByte + NumByteToRead_up_to_PageSize) > w25qxx.PageSize)
    NumByteToRead_up_to_PageSize = w25qxx.PageSize - OffsetInByte;
#if (_W25QXX_DEBUG == 1)
  printf("w25qxx ReadPage:%ld, Offset:%ld ,Read %ld Bytes, begin...\r\n", Page_Address, OffsetInByte, NumByteToRead_up_to_PageSize);
  W25qxx_Delay(100);
  uint32_t StartTime = HAL_GetTick();
#endif
  Page_Address = Page_Address * w25qxx.PageSize + OffsetInByte;
  _W25QXX_CS_(0);
  W25qxx_Spi(FAST_READ);
  if (w25qxx.ID >= W25Q256)
    W25qxx_Spi((Page_Address & 0xFF000000) >> 24);
  W25qxx_Spi((Page_Address & 0xFF0000) >> 16);
  W25qxx_Spi((Page_Address & 0xFF00) >> 8);
  W25qxx_Spi(Page_Address & 0xFF);
  W25qxx_Spi(0);
  W25qxx_Receive(pBuffer, NumByteToRead_up_to_PageSize);
  _W25QXX_CS_(1);
#if (_W25QXX_DEBUG == 1)
  StartTime = HAL_GetTick() - StartTime;
  for (uint32_t i = 0; i < NumByteToRead_up_to_PageSize; i++)
  {
    if ((i % 8 == 0) && (i > 2))
    {
      printf("\r\n");
      W25qxx_Delay(10);
    }
    printf("0x%02X,", pBuffer[i]);
  }
  printf("\r\n");
  printf("w25qxx ReadPage done after %ld ms\r\n", StartTime);
  W25qxx_Delay(100);
#endif
  W25qxx_Delay(1);
  w25qxx.Lock = 0;
}

/**
 * @function: void W25qxx_ReadSector(uint8_t *pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_SectorSize)
 * @description: 扇区读取
 * @param {uint8_t} *pBuffer 读取的数据
 * @param {uint32_t} Sector_Address 读取的扇区地址
 * @param {uint32_t} OffsetInByte
 * @param {uint32_t} NumByteToRead_up_to_SectorSize
 * @return {*}
 */
void W25qxx_ReadSector(uint8_t *pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_SectorSize)
{
  if ((NumByteToRead_up_to_SectorSize > w25qxx.SectorSize) || (NumByteToRead_up_to_SectorSize == 0))
    NumByteToRead_up_to_SectorSize = w25qxx.SectorSize;
#if (_W25QXX_DEBUG == 1)
  printf("+++w25qxx ReadSector:%ld, Offset:%ld ,Read %ld Bytes, begin...\r\n", Sector_Address, OffsetInByte, NumByteToRead_up_to_SectorSize);
  W25qxx_Delay(100);
#endif
  if (OffsetInByte >= w25qxx.SectorSize)
  {
#if (_W25QXX_DEBUG == 1)
    printf("---w25qxx ReadSector Faild!\r\n");
    W25qxx_Delay(100);
#endif
    return;
  }
  uint32_t StartPage;
  int32_t BytesToRead;
  uint32_t LocalOffset;
  if ((OffsetInByte + NumByteToRead_up_to_SectorSize) > w25qxx.SectorSize)
    BytesToRead = w25qxx.SectorSize - OffsetInByte;
  else
    BytesToRead = NumByteToRead_up_to_SectorSize;
  StartPage = W25qxx_SectorToPage(Sector_Address) + (OffsetInByte / w25qxx.PageSize);
  LocalOffset = OffsetInByte % w25qxx.PageSize;
  do
  {
    W25qxx_ReadPage(pBuffer, StartPage, LocalOffset, BytesToRead);
    StartPage++;
    BytesToRead -= w25qxx.PageSize - LocalOffset;
    pBuffer += w25qxx.PageSize - LocalOffset;
    LocalOffset = 0;
  } while (BytesToRead > 0);
#if (_W25QXX_DEBUG == 1)
  printf("---w25qxx ReadSector Done\r\n");
  W25qxx_Delay(100);
#endif
}

/**
 * @function: void W25qxx_ReadBlock(uint8_t *pBuffer, uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_BlockSize)
 * @description: 块读取
 * @param {uint8_t} *pBuffer 读取的数据
 * @param {uint32_t} Block_Address 读取的块地址
 * @param {uint32_t} OffsetInByte
 * @param {uint32_t} NumByteToRead_up_to_BlockSize
 * @return {*}
 */
void W25qxx_ReadBlock(uint8_t *pBuffer, uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_BlockSize)
{
  if ((NumByteToRead_up_to_BlockSize > w25qxx.BlockSize) || (NumByteToRead_up_to_BlockSize == 0))
    NumByteToRead_up_to_BlockSize = w25qxx.BlockSize;
#if (_W25QXX_DEBUG == 1)
  printf("+++w25qxx ReadBlock:%ld, Offset:%ld ,Read %ld Bytes, begin...\r\n", Block_Address, OffsetInByte, NumByteToRead_up_to_BlockSize);
  W25qxx_Delay(100);
#endif
  if (OffsetInByte >= w25qxx.BlockSize)
  {
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx ReadBlock Faild!\r\n");
    W25qxx_Delay(100);
#endif
    return;
  }
  uint32_t StartPage;
  int32_t BytesToRead;
  uint32_t LocalOffset;
  if ((OffsetInByte + NumByteToRead_up_to_BlockSize) > w25qxx.BlockSize)
    BytesToRead = w25qxx.BlockSize - OffsetInByte;
  else
    BytesToRead = NumByteToRead_up_to_BlockSize;
  StartPage = W25qxx_BlockToPage(Block_Address) + (OffsetInByte / w25qxx.PageSize);
  LocalOffset = OffsetInByte % w25qxx.PageSize;
  do
  {
    W25qxx_ReadPage(pBuffer, StartPage, LocalOffset, BytesToRead);
    StartPage++;
    BytesToRead -= w25qxx.PageSize - LocalOffset;
    pBuffer += w25qxx.PageSize - LocalOffset;
    LocalOffset = 0;
  } while (BytesToRead > 0);
#if (_W25QXX_DEBUG == 1)
  printf("---w25qxx ReadBlock Done\r\n");
  W25qxx_Delay(100);
#endif
}
