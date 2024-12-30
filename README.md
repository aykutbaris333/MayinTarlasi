# MayinTarlasi
Proje konsol üstünden oynanan bir mayın tarlası oyunudur.
İlk başta kullanıcıdan oyun tahtasının kaç satır ve sutundan oluştuğunu ve zorluk inputunu alır. İnputa göre iki adet iki boyutlu matris kurar: gtahta ve stahta.
gtahta içinde mayın ve sayıların olduğu tahtadır, oyun kazanma-kaybetme kontrolu de bu tahta üzerinden yapılır. Satir sutun ve zorluk inputu alındığı zaman mayınlar bu tahtanın içine rastgele dağıtılır.
stahta ise açılan karelerin gtahtadan alınarak atandığı ve oycuya hangi karenin açık hangisinin kapalaı olduğu göstermek için kullanılır.
Oyun tahtalarının kurulmasından sonra sonsuz döngüye girilip kullanıcıdan satır ve sutun girdisi alındıktan sonra   kare aç/bayrak koy   seçimi verilir.
Kare açılmasında açılan kare mayınsa kaybettin mesajı verilip program sonlandırılır, eğer açılan kare son açılabilir kare ise kazandın mesajı verilir program sonlandırılır, ikisi de olmazsa döngü başa sarar.
