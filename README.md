### ILGA Tokens

This tokens can be placed in the markup text of webforms to fill in specific details from CiviCRM. The forms are used to comment on de information in a Case. To identify the case the parameter `case1=<caseid>` must be added to the url of the case. The following tokens are defined:

`[current-page:casefield:fieldid]`. The fieldid is the identifier of the field that must be used to pull in the custom field. If nothing can be found, nothing is shown. The result is formatted as `<label>:<formatted value>`.

`[current-page:casetext:fieldid]`.
The same as above but now in the following format

````
<label><br/>
<p><formatted value</p>
