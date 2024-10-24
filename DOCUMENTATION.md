![[poker.drawio.png]]

### Game
### XiDachEngine
### PokerEngine
### Leaderboard
### Player
### Hand
### Card
### HandType
Dùng để phân loại tay bài của người chơi, đồng thời để ghi lại thông số về chiến thuật.
#### Đối với Poker:
- (nếu có lá joker)`FiveOfAKind`: tứ quý và 1 lá joker
- `StraightFlush`: sảnh 5, đồng chất
- `FourOfAKind`: tứ quý
- `FullHouse`: 1 đôi, 1 ba
- `Flush`: 5 lá đồng chất
- `Straight`: sảnh 5
- `ThreeOfAKind`: 3 lá cùng hạng
- `TwoPair`: 2 đôi
- `OnePair`: 1 đôi
- `HighCard`: bài cao
#### Đối với xì dách / xì lát:
- `XiBan`: xì bàn
- `XiDach`: xì dách
- `NguLinh`: ngũ linh
- `Quac`: quắc (rút quá 21 nút)
### GameMode
- `basic`: Biến thể cơ bản của poker, deal mỗi người chơi 5 lá úp, sau đó đặt cược cho tới khi chỉ còn lại 1 người hoặc không còn ai muốn tăng cược. 2-8 người chơi.
- `texas`: Giống `basic`, nhưng lúc đầu mỗi người được deal 2 lá úp, sau đó deal 5 lá úp chung, sau đó lần lượt mở từng lá, đặt cược giữa những lần mở. Khi mở hết 5 lá thì tiếp tục đặt cược giống như `basic`. 2-8 người chơi.
- `xidach`: Bài xì dách / xì lát (luật chơi thì chắc mọi người đều biết r, nếu chưa biết thì [wiki](https://vi.wikipedia.org/wiki/X%C3%AC_d%C3%A1ch)). Lúc đầu deal mỗi người chơi 2 lá úp, sau đó mỗi người lần lượt rút bài, đếm nút. 2-8 người chơi