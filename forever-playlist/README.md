# Forever Playlist

This little project will create a music player with a teensy 4.0 and the audio shield, 
that will play the files in your SD card on repeat, over an over forever.


### Notes

Getting good audio files..

This is surprisingly hard these days with streaming music apps. It seems you can buy music on 
amazon or apple music. Amazon only will allow you to download mp3's so i dont really like
that, i would really like wav or someother lossless format like ALAC or FLAC.

When buying music from apple music, you download the file in .m4a file, which is just a 
container that can hold either aac (lossy) or alac (lossless) data formats.

To determine what type of data your .m4a has inside, you can run this
```
afinfo {filename}
```

So apparently Apple music only allows you to download music in aac to keep and play offline. 
The only way i have found so far is https://www.qobuz.com/ which allows you to buy the album 
and download in almost all formats.

Teensy audio [GitHub](https://github.com/PaulStoffregen/Audio)

Im using this for a forever BTBAM player, here is their discography in order.

 - Between the Buried and me 
 - The Silent Circus
 - Alaska
 - Colors
 - The Great Misdirect
 - The Parallax: Hypersleep Dialogues
 - The Parallax II: Future Sequence
 - Coma Ecliptic 
 - Automata I
 - Automata II
 - Colors II