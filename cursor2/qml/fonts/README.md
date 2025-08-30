# Ubuntu 字体说明

## 获取 Ubuntu 字体

### 方法1：从 Ubuntu 官方下载
1. 访问 https://design.ubuntu.com/font/
2. 下载 Ubuntu 字体包
3. 将 `Ubuntu-Regular.ttf` 文件放置在此目录

### 方法2：从系统安装
```bash
# Ubuntu/Debian
sudo apt install fonts-ubuntu

# 然后复制字体文件
sudo cp /usr/share/fonts/truetype/ubuntu/Ubuntu-Regular.ttf ./qml/fonts/
```

### 方法3：使用 Google Fonts
```bash
# 下载 Google Fonts 版本的 Ubuntu
wget https://fonts.gstatic.com/s/ubuntu/v20/4iCs6KVjbNBYlgo6eA.ttf -O Ubuntu-Regular.ttf
```

## 字体文件要求

- 文件名：`Ubuntu-Regular.ttf`
- 格式：TrueType (.ttf)
- 大小：约 200-300 KB

## 注意事项

- 确保字体文件具有正确的读取权限
- 如果字体加载失败，程序将回退到系统默认字体
- 字体文件会增加应用程序的大小，但提供更好的视觉体验

## 许可证

Ubuntu 字体采用 Ubuntu Font Licence，详情请访问：
https://design.ubuntu.com/font/
