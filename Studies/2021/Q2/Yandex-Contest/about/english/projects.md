# Design part of the

The formulation of the 2021 projects has not yet been finalized, but those interested can see examples of the 2020 projects:

## Project 1. Dish-ID: all about food in one photo

*General description of the project/data*

The project proposes to implement a model that determines the composition of a dish, its calorie content, and offers several possible recipes based on a photo of a meal. On the basis of this model, you need to additionally make an application or telegram bot.

*Statement of the problem*

The goal of the project is to build a machine learning model that determines the name of a dish from a photo, and then selects its composition, calorie content and recipe. The solution of this problem is carried out in several stages. The first step is to train a model that recognizes the food in the photo and generates the name of the dish. At the second stage, the name of the dish determines its composition, calorie content and the recipe is selected. To solve each of the subtasks, there are a number of methods from the field of Computer Vision and Natural Language Processing. As training data, it is proposed to use a dataset with annotated photos from open sources (for example, Kaggle competitions). The main focus of the project will be on adapting the known algorithms to the specifics of a particular task and combining all the stages into a single model. In addition, you will need to collect data on recipes from open sources.

*A description of the data*

To implement the first stage (food recognition by image), it is supposed to take a dataset from the Kaggle competition (https://www.kaggle.com/artgor/food-recognition-challenge-eda). At the second stage (determining the composition, calorie content and selection of the recipe), you will need to independently collect data from open sources.

*The desired result*

The final result will be a trained machine learning model, ideally implemented in the form of an android app or a telegram bot, which will generate its composition, calorie content and offer a possible recipe based on a photo of a dish.

## Project #2. Chatbot on the topic

*General description of the project/data*

Only recently have people been able to teach neural networks to generate plausible and unique passages of text. However, this is only part of the problem, in fact, it is interesting to get a controlled text generation. For example, make the neural network talk only about window sills or cats.

It is necessary to develop a chatbot that will play a word game with the user.

*Statement of the problem*

The challenge is to apply and slightly improve the existing approaches of controlled text generation (for example, https://arxiv.org/abs/1912.02164). We will use these techniques to develop a word game in which the user will need to "convince" the bot to respond in a certain way in order to move on to the next step of the game.

*A description of the data*

It will use data from open sources — forums, entertainment sites, social networks, and so on.

*The desired result*

As a final result, a simple chatbot in Russian will be developed, which you can talk to in telegram.

## Project #3. Automating form filling

*General description of the project/data*

At the moment, many specialists fill out a report form based on the results of their work, which leads to time costs. On the other hand, the quality of filling out the forms leaves much to be desired. The goal of the project is to create a mobile application for Android that can record the speech of a specialist and automatically fill out a form in a fixed format.

To create this application, you need to develop and test a speech recognition algorithm.

*Statement of the problem*

The task is to build a machine learning model that is trained on the data of audio recordings of Russian speech with the markup of recognition results (text). You need to test the existing libraries and try to develop your own algorithm. It is proposed to use neural networks to recognize phonemes and then letters and words.

*The desired result*

As a final result, a group of students should provide predictions of the target variable, a report-description of the work done, and a non-trivial implemented algorithm for data preprocessing.

Additionally (but not necessarily), an application prototype with an embedded model can be developed.
