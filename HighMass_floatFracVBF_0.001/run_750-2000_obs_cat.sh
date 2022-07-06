
cat=$1

for type in 1D 2D

  do

  echo ${type}
  for ((n=0; n<13;n++))

    do

      mH=$((750+50*${n}))

      echo ${mH}
      cd ../cards_sm13_${type}_12p9fb_fracVBF_0.001_floatFracVBF/HCG/${mH}/
      echo 'obs'
      combine -n mH${mH}_${cat}_obs -m ${mH} -M Asymptotic hzz2l2q_${cat}_13TeV.txt --rMax 1 > ${type}_mH${mH}_${cat}_obs.log

      cd -

    done

  for ((n=0; n<13;n++))

    do

      mH=$((1400+50*${n}))

      echo ${mH}
      cd ../cards_sm13_${type}_12p9fb_fracVBF_0.001_floatFracVBF/HCG/${mH}/
      echo 'obs'      
      combine -n mH${mH}_${cat}_obs -m ${mH} -M Asymptotic hzz2l2q_${cat}_13TeV.txt --rMax 0.035 > ${type}_mH${mH}_${cat}_obs.log

      cd -

    done


  done 

