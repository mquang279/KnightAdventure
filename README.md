# Knight Adventure - 23021669 Bùi Minh Quang
Dự án trò chơi này là một phần của môn học "Lập trình nâng cao" tại Trường Đại học Công nghệ - Đại học Quốc gia Hà Nội.

# Mô tả
- Dự án này được phát triển bằng __ngôn ngữ lập trình C++__ và sử dụng __thư viện SDL2__.
- Dự án được lấy cảm hứng từ tựa game __Dead Cells__ và __Dan the Man__.
- Trong __Knight Adventure__, người chơi sẽ bước vào một thế giới phong phú đầy màu sắc và mạo hiểm. Họ sẽ nhập vai vào một chiến binh dũng mãnh, sẵn sàng đối đầu với những thử thách khốc liệt, những quái vật cản đường và tiến lên phía trước.

# Cách tải game
- Bước 1: [Tải xuống](https://github.com/mquang09/KnightAdventure/archive/refs/heads/master.zip) và giải nén file `KnightAdventure-master.zip`.
- Bước 2: Vào thư mục `KnightAdventure` nơi chứa file cpp và chạy file `KnightAdventure.exe` để bắt đầu chơi.

# Hướng dẫn chơi
## Giao diện ban đầu
![image](https://github.com/mquang09/KnightAdventure/assets/101109835/0437b470-a206-4f70-95bf-225cd683a8a9)
Gồm có 3 lựa chọn: `Play`, `Help`, `About`.

__1. `Help` Menu__
![image](https://github.com/mquang09/KnightAdventure/assets/101109835/4941e89b-1c06-4085-b38d-c7683eab4ff3)
- Người chơi có thể di chuyển nhân vật bằng hai phím mũi tên `⬅` `⮕`.
- Người chơi có thể thực hiện đánh bằng cách __giữ phím__ `SPACE`.
- Người chơi có thể nhảy bằng phím `⬆`.

__2. `About` Menu__
![image](https://github.com/mquang09/KnightAdventure/assets/101109835/e253d8ef-b13a-4072-9c5b-cca6c08ac1b7)
Trong phần `About` sẽ có mô tả về dự án game __Knight Adventure__

__3. `Play` Menu__
![image](https://github.com/mquang09/KnightAdventure/assets/101109835/9c7dcf60-df58-4d74-ae5f-1d9a7dbcddc4)
Hiển thị những __Level__ cho người chơi lựa chọn. Có tổng cộng 18 __Level__.

## Giao diện chơi game
__1. Thanh máu__

![image](https://github.com/mquang09/KnightAdventure/assets/101109835/8bd4b9b7-89a7-4e42-93cb-124d4b044f45)

Người chơi sẽ bắt đầu với 8 máu, trò chơi sẽ kết thúc khi lượng máu trở về 0.


__2. Quái vật__

| Quái vật | Mô tả |
| -------- | ----- |
| ![image](https://github.com/mquang09/KnightAdventure/assets/101109835/de0f6ea0-1c35-4cdd-a8fb-f0049a109932) | Burning Ghoul |
| ![image](https://github.com/mquang09/KnightAdventure/assets/101109835/6fac1989-a79f-4507-86e4-30ca424e56a8) | Spectral Wraith |
| ![image](https://github.com/mquang09/KnightAdventure/assets/101109835/593448a9-7d6a-4a26-891b-e35284d9ed7a) | Hellhound |

Tốt nhất là đừng chạm vào chúng nếu bạn không muốn mất mạng!!!

__3. Bẫy__

![image](https://github.com/mquang09/KnightAdventure/assets/101109835/7bd4e848-da85-4c30-a64d-fdf7901ab59d)

Rất sắc nhọn và có thể khiến bạn chảy máu nếu chạm vào chúng!!!

__4. Thuốc hồi máu__

![image](https://github.com/mquang09/KnightAdventure/assets/101109835/341d4549-02a6-451e-8cb9-75d35a78ee17)

Xuất hiện ngẫu nhiên trên map, khi sử dụng sẽ hồi lại cho người chơi 1 máu đã mất.

__5. Tảng đá ma thuật__

![image](https://github.com/mquang09/KnightAdventure/assets/101109835/101e54b9-9924-4876-bb34-b08aef4b9c27)

Khi người chơi rơi xuống vực thẳm, tảng đá sẽ dịch chuyển người chơi về lại chỗ của nó.

__6. Cổng dịch chuyển__

![image](https://github.com/mquang09/KnightAdventure/assets/101109835/a97989bf-d762-441b-8d51-8ee062a1cea4)

Có khả năng giúp người chơi dịch chuyển sang màn chơi khác.

__7. Màn hình kết thúc__

![image](https://github.com/mquang09/KnightAdventure/assets/101109835/4c3d227f-7353-440a-9e4b-db2318c6cf0f)

Khi lượng máu của người chơi trở về 0. Màn hình kết thúc sẽ hiện ra:
- Nếu chọn `Play Again` người chơi sẽ được hồi sinh tại vị trí ban đầu của Level và trò chơi sẽ bắt đầu lại từ đầu.
- Nếu chọn `Home` màn hình sẽ chuyển về `Giao diện ban đầu`.

__8. Màn hình hoàn thành__

![image](https://github.com/mquang09/KnightAdventure/assets/101109835/cc782ce6-b2ff-49f3-b3df-5872a26a4624)

Khi người chơi đi đến cuối bản đồ (Đã hoàn thành màn chơi). Màn hình hoàn thành sẽ hiện ra:
- Nếu chọn `Next Level` thì `Cổng dịch chuyển` sẽ đưa người chơi đến màn chơi tiếp theo.
- Nếu chọn `Home` màn hình sẽ chuyển về `Giao diện ban đầu`.





