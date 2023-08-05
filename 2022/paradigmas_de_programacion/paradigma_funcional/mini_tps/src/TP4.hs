module TP4 where
import ContenidoAudiovisual

-- PUNTO 1
tieneHashtag :: String -> Video -> Bool
tieneHashtag hashtag = elem hashtag . hashtags

-- PUNTO 2
minutosTotalesConHashtag :: String -> Playlist -> Int
minutosTotalesConHashtag hashtag = sumarMinutosVideos . separarVideosConHashtag hashtag . videos

-- abstracciones punto 2
separarVideosConHashtag :: String -> [Video] -> [Video]
separarVideosConHashtag hashtag = filter $ tieneHashtag hashtag

sumarMinutosVideos :: [Video] -> Int
sumarMinutosVideos = sum . (map minutos)

-- PUNTO 3
estanRelacionados :: Video -> Video -> Bool
estanRelacionados video1 = any (`tieneHashtag` video1) . hashtags

-- PUNTO 4
recomendable :: Video -> Playlist -> Bool
recomendable video = (> 1) . length . (filtrarVideosRelacionados video) . videos

-- abstracciones punto 4
filtrarVideosRelacionados :: Video -> [Video] -> [Video]
filtrarVideosRelacionados video = filter $ estanRelacionados video

-- PUNTO 5
agregarVideosRecomendados :: [Video] -> Playlist -> Playlist
agregarVideosRecomendados videos playlist = foldr (agregarAPlaylistSoloSi recomendable) playlist videos