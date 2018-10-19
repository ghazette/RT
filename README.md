# RT

## Introduction

  Le ray tracing, est une technique de calcul d'optique par ordinateur, utilisée pour le rendu en synthèse d'image ou pour des études de systèmes optiques. Elle consiste à simuler le parcours inverse de la lumière : on calcule les éclairages de la caméra vers les objets, puis vers les lumières, alors que dans la réalité, la lumière va de la scène vers l'œil.

  Cette technique reproduit les phénomènes physiques (principe du retour inverse de la lumière de Fermat, lois de Snell-Descartes) que sont la réflexion et la réfraction. Une mise en œuvre naïve du ray tracing ne peut rendre compte de phénomènes optiques tels que les caustiques, l'illumination globale ou encore la dispersion lumineuse (il faut une approche plus élaborée du ray tracing faisant appel à des techniques probabilistes de type méthode de Monte-Carlo, Metropolis ou à la radiosité pour résoudre ces problèmes).

En revanche, contrairement à d'autres algorithmes de synthèse d'image, elle permet de définir mathématiquement les objets à représenter et non pas seulement par une multitude de facettes.

## Objectifs

  Votre objectif est d’être capable, à l’aide de votre programme, de générer des images de synthèse selon la méthode du Ray-Tracing. Ces images de synthèse représentent une scène, vue d’une position et d’un angle spécifiques, définie par des objets géométriques simples, entiers ou partiels, et disposant d’un système d’éclairage.
  
  Le projet comporte une partie obligatoire et de nombreuses options. La partie obligatoire vaut 0 points et les options ne rapportent des points que si la partie obligatoire est complète à 100%. Le projet ne sera validé que si un volume substanciel d’options est présent lors de la soutenance.

## How to

```
make
```

```
./RT scenes/scene_name.scene
```

## Fonctionnalités

 <table>
   <tr>
       <td>LEFT CLICK</td>
       <td>Passer de la scène à l'interface et inversement</td>
   </tr>
   <tr>
       <td>UP</td>
       <td>Déplacer caméra / objet vers le haut</td>
   </tr>
   <tr>
       <td>LEFT</td>
       <td>Déplacer caméra / objet vers la gauche</td>
   </tr>
   <tr>
       <td>DOWN</td>
       <td>Déplacer caméra / objet vers le bas</td>
   </tr>
   <tr>
       <td>RIGHT</td>
       <td>Déplacer caméra / objet vers la droite</td>
   </tr>
   <tr>
       <td>+</td>
       <td>Déplacer caméra / objet vers l'arrière</td>
   </tr>
   <tr>
       <td>-</td>
       <td>Déplacer caméra / objet vers l'avant</td>
   </tr>
   <tr>
       <td>8 / 2</td>
       <td>Pivoter caméra / objet sur l'axe X</td>
   </tr>
   <tr>
       <td>4 / 6</td>
       <td>Pivoter caméra / objet sur l'axe Y</td>
   </tr>
   <tr>
       <td>7 / 9</td>
       <td>Pivoter caméra / objet sur l'axe Z</td>
   </tr>
   <tr>
       <td>F</td>
       <td>Changer de filtre</td>
   </tr>
   <tr>
       <td>Page up / Page down</td>
       <td>Faire varier l'anti-aliasing</td>
   </tr>
   <tr>
       <td>ESC</td>
       <td>Quitter le programme</td>
   </tr>
</table>

## Exemples

### Showcase
![img](https://i.imgur.com/AZeZWBb.png)

### Sphere World
![img](https://i.imgur.com/P8zaw6g.png)

### Planet
![img](https://i.imgur.com/mBQM0oQ.png)

### Plane
![img](https://i.imgur.com/RnwoybS.png)

### Glock
![img](https://i.imgur.com/gsizqPg.png)

## Live

### Filters
![](https://media.giphy.com/media/g07eqj1eI189NG22MG/giphy.gif)

### Pokeball
![](https://media.giphy.com/media/5jYu1do9s68fyar9Kh/giphy.gif)

### Texture
![](https://media.giphy.com/media/2rAEVexWLWyYlFUPK1/giphy.gif)

### Last but not least
![](https://media.giphy.com/media/5zgZUjSL4Pmd6G8gEM/giphy.gif)

## Authors
[Lossy Roméo](https://github.com/Althis974)

[Hazette Grégoire](https://github.com/kryme07)

[Kulhandjian Mathias](https://github.com/Gozelin)
