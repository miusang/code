fps_count=0
i=0
rawData=$(service call SurfaceFlinger 1013)
strData=${rawData#*\(}
strData=${strData%% *}
lastCount=$((16#${strData}))
while true
do
    sleep 1
    rawData=$(service call SurfaceFlinger 1013)
    echo str is $rawData
    strData=${rawData#*\(}
    echo str is $strData
    strData=${strData%% *}
    echo str is $strData
    count=$((16#${strData}))
    i=`expr $i + 1`
    fps=$((count - lastCount))
    fps_count=`expr $fps_count + $fps`
    fps_avg=`expr $fps_count / $i`
    echo time is $i
    echo fps is $fps
    #echo fps_count is $fps_count
    echo fps_agv is $fps_avg
    lastCount=$count
done
